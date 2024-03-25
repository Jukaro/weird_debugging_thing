#pragma once

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <errno.h>

#include "utils/get_next_line_bonus.h"

#define RED "\e[38;2;255;000;000m"
#define GREEN "\e[38;2;000;255;000m"
#define BLUE "\e[38;2;000;000;255m"
#define ORANGE "\e[38;2;255;150;000m"
#define YELLOW "\e[38;2;255;255;000m"
#define PURPLE "\e[38;2;255;000;225m"
#define NRM "\e[m"
#define CLR "\e[?0K"

#define PROTECTED "\e[1\"q"
#define UNPROTECTED "\e[0\"q"

#define SEP 60
#define PADDING 5
#define HEIGHT 45

#define clear() printf("\e[H\e[J")
#define gotoxy(x,y) printf("\e[%d;%dH", (x), (y))

typedef struct	s_info
{
	char	*info;
	char	*name;
	int		row;
	int		col;
}				t_info;

typedef struct	s_dbg_info
{
	int		pipe[2];
	char	*name;
	char	*category_title;
	t_info	*info_array;
	char	*color;
	int		counter;
	struct s_dbg_info	*next;
}				t_dbg_info;

/* ---------------------------------- FORK ---------------------------------- */

void	wait_childs(void);
void	start_fork(int fd, t_dbg_info *list, char *path);

/* ---------------------------------- INFO ---------------------------------- */

int		dbg_list_size(t_dbg_info *list);
void	dbg_free_list(t_dbg_info **list);
void	init_dbg_lists(t_dbg_info **r_list, t_dbg_info **e_list);
void	free_d_info(t_dbg_info *info);
int		print_info(t_dbg_info *info, int row, int col);

/* ---------------------------------- PIPE ---------------------------------- */

void	init_pipes(t_dbg_info *list);
void	print_pipe(t_dbg_info *list, int col);

/* ----------------------------- PRINT SKELETON ----------------------------- */

void	print_skeleton_part(t_dbg_info *list, int row, int col);
void	print_skeleton(t_dbg_info *r_list, t_dbg_info *e_list);

/* --------------------------------- SIGNAL --------------------------------- */

void	sigint_handler(int signum);
