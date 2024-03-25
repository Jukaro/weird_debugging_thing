#include "launcher.h"

void	sigint_handler(int signum)
{
	gotoxy(HEIGHT, 1);
	printf("\n\e[?25h");
	exit(130);
}
