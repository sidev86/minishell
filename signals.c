#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		errors_manager(SET_CODE, 130, NULL, NULL);
		//signals_controller(SET, true);
	}
}
