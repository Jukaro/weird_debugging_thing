#include "launcher.h"

void	print_skeleton_part(t_dbg_info *list, int row, int col)
{
	for (t_dbg_info *ptr = list; ptr; ptr = ptr->next)
	{
		gotoxy(row, col);
		// print category title
		printf("%s%s------ %s ------%s%s", PROTECTED, BLUE, ptr->category_title, NRM, UNPROTECTED);
		row++;
		for (int i = 0; ptr->info_array[i].name; i++)
		{
			gotoxy(row, col);
			// print info name
			printf("%s%s%s: %s%s", PROTECTED, ptr->color, ptr->info_array[i].name, NRM, UNPROTECTED);
			ptr->info_array[i].row = row;
			ptr->info_array[i].col = strlen(ptr->info_array[i].name) + 3 + col;
			row++;
		}
		row++;
	}
}

void	print_skeleton(t_dbg_info *r_list, t_dbg_info *e_list)
{
	for (int i = 1; i < HEIGHT; i++)
	{
		gotoxy(i, SEP);
		printf("%s|%s", PROTECTED, UNPROTECTED);
	}

	int	r_size = dbg_list_size(r_list);
	int	e_size = dbg_list_size(e_list);

	print_pipe(r_list, 1);
	print_pipe(e_list, SEP + PADDING);

	int	r_row = 1 + (r_size + 1) * 2;
	int	e_row = 1 + (e_size + 1) * 2;
	int	row = r_row > e_row ? r_row : e_row;

	gotoxy(row, 1);
	printf("==================== RECEPTEUR ====================");
	gotoxy(row, SEP + PADDING);
	printf("==================== EMETTEUR ====================");

	row += 2;

	print_skeleton_part(r_list, row, 0);
	print_skeleton_part(e_list, row, SEP + PADDING);
}
