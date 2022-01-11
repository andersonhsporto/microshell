#include "microshell.h"

void	clear(void)
{
	printf("\033[H\033[J");
}

void	init_shell(void)
{
	char	*username;

	username = getenv("USER");
	clear();
	printf("\n\n\n\n******************""************************");
	printf("\n\n\n\t****MY SHELL****");
	printf("\n\n\t-USE AT YOUR OWN RISK-");
	printf("\n\n\n\n*******************""***********************");
	printf("\n\n\nUSER is: @%s", username);
	printf("\n");
	sleep(1);
	clear();
}
