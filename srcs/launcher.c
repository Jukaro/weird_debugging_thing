#include "launcher.h"

void	init(int *rfd, int *efd)
{
	// chdir("..");

	signal(SIGINT, &sigint_handler);

	printf("\e[?25l");

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	*rfd = open("r_out.ansi", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	*efd = open("e_out.ansi", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*rfd == -1 || *efd == -1)
	{
		perror("Can't create / open log files");
		exit(1);
	}

	clear();
}

int		watch_fds(int max_fd, fd_set *read_fds, struct timeval *timeout, t_dbg_info *r_list, t_dbg_info *e_list)
{
	timeout->tv_sec = 10;
	timeout->tv_usec = 0;

	FD_ZERO(read_fds);
	for (t_dbg_info *ptr = r_list; ptr; ptr = ptr->next)
		FD_SET(ptr->pipe[0], read_fds);
	for (t_dbg_info *ptr = e_list; ptr; ptr = ptr->next)
		FD_SET(ptr->pipe[0], read_fds);

	return (select(max_fd + 1, read_fds, NULL, NULL, timeout));
}

void	main_loop(t_dbg_info *r_list, t_dbg_info *e_list)
{
	int				trggrd_fd;
	struct timeval	timeout;
	int				r_size = dbg_list_size(r_list);
	int				e_size = dbg_list_size(e_list);
	int				nb_pipes = r_size + e_size;
	int				max_fd = 4 + nb_pipes * 2;
	fd_set			read_fds;
	int				stop = 0;

	trggrd_fd = watch_fds(max_fd, &read_fds, &timeout, r_list, e_list);

	while (trggrd_fd && !stop)
	{
		gotoxy(r_size + 1, SEP);
		printf("\e[?1K");
		gotoxy(r_size + 1, 1);
		printf("fds:");
		for (t_dbg_info *ptr = r_list; ptr; ptr = ptr->next)
			if (FD_ISSET(ptr->pipe[0], &read_fds))
				printf(" %d", ptr->pipe[0]);
		for (t_dbg_info *ptr = e_list; ptr; ptr = ptr->next)
			if (FD_ISSET(ptr->pipe[0], &read_fds))
				printf(" %d", ptr->pipe[0]);

		int	row = 0;

		for (t_dbg_info *ptr = r_list; ptr; ptr = ptr->next, row++)
			if (FD_ISSET(ptr->pipe[0], &read_fds) && print_info(ptr, 2 + r_size + row, 1))
				stop = 1;

		row = 0;
		for (t_dbg_info *ptr = e_list; ptr; ptr = ptr->next, row++)
			if (FD_ISSET(ptr->pipe[0], &read_fds) && print_info(ptr, 2 + e_size + row, SEP + PADDING))
				stop = 1;

		trggrd_fd = watch_fds(max_fd, &read_fds, &timeout, r_list, e_list);
	}
	// close all pipes reads
	for (t_dbg_info *ptr = r_list; ptr; ptr = ptr->next)
		close(ptr->pipe[0]);
	for (t_dbg_info *ptr = e_list; ptr; ptr = ptr->next)
		close(ptr->pipe[0]);

	gotoxy(HEIGHT, 1);
	if (trggrd_fd)
		printf("\nsorti de la boucle: break");
	else
		printf("\nsorti de la boucle: select");
}

int	main()
{
	int			r_fd;
	int			e_fd;
	t_dbg_info	*r_dbg_list = NULL;
	t_dbg_info	*e_dbg_list = NULL;

	init(&r_fd, &e_fd);

	init_dbg_lists(&r_dbg_list, &e_dbg_list);

	init_pipes(r_dbg_list);
	init_pipes(e_dbg_list);

	start_fork(r_fd, r_dbg_list, "./bin/recepteur");
	usleep(100000);
	start_fork(e_fd, e_dbg_list, "./bin/emetteur");

	print_skeleton(r_dbg_list, e_dbg_list);
	main_loop(r_dbg_list, e_dbg_list);
	wait_childs();

	dbg_free_list(&r_dbg_list);
	dbg_free_list(&e_dbg_list);

	printf("\n\n");
	printf("\n\e[?25h");

	return (0);
}
