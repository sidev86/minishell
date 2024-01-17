#include "minishell.h"

void	signal_handler(int sig)
{
	//printf("signal number = %d\n", sig);
	if (sig == SIGINT)
	{
		
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		errors_manager(SET_CODE, 130, NULL, NULL);
	}
}
