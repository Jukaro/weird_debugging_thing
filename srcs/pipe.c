#include "launcher.h"

void	init_pipes(t_dbg_info *list)
{
	for (t_dbg_info *ptr = list; ptr; ptr = ptr->next)
	{
		if (pipe(ptr->pipe))
		{
			dprintf(2, "%s's pipe: %s", ptr->category_title, strerror(errno));
			return;
		}
	}
}

void	print_pipe(t_dbg_info *list, int col)
{
	int	row = 1;

	for (t_dbg_info *ptr = list; ptr; ptr = ptr->next)
	{
		gotoxy(row, col);
		printf("%s([0]: %d, [1]: %d)\n", ptr->name, ptr->pipe[0], ptr->pipe[1]);
		row++;
	}
}
