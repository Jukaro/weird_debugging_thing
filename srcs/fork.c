#include "launcher.h"

void	wait_childs(void)
{
	pid_t	wpid;

	wpid = 1;
	while (wpid > 0)
		wpid = wait(NULL);
}

void	start_fork(int fd, t_dbg_info *list, char *path)
{
	pid_t	pid;
	char	**argv;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		argv = malloc(sizeof(char *) * 2);
		argv[0] = path;
		argv[1] = NULL;
		// close all child pipes reads
		for (t_dbg_info *ptr = list; ptr; ptr = ptr->next)
			close(ptr->pipe[0]);
		dup2(fd, 1);
		close(fd);
		if (execve(argv[0], argv, NULL))
			perror("execve");
	}
	// close all parent pipes writes
	for (t_dbg_info *ptr = list; ptr; ptr = ptr->next)
			close(ptr->pipe[1]);
}
