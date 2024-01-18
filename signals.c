#include "minishell.h"

void	signal_handler(int sig)
{
	//printf("signal number = %d\n", sig);
	if (sig == SIGINT)
	{
		
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (signal_no_input(GET_CODE, 1))
			rl_redisplay();
		errors_manager(SET_CODE, 130, NULL, NULL);
	}
}


int	signal_no_input(int action, int code)
{
	static int no_input;
	if (action == SET_CODE)
		no_input = code;
	if (action == GET_CODE)
		return(no_input);
	return(0);
}


