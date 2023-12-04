#include "minishell.h"

int	errors_manager(int action, int code, char *msg, char *arg)
{
	static int exit_code;
	char *msg_full;
	msg_full = 0;
	if (action == GET_CODE)
		return (exit_code);
	else if (action == SET_CODE)
		exit_code = code;
	else if (action == PRINT)
	{
		msg_full = ft_strcat(arg, ": ");
		msg_full = ft_strcat(msg_full, msg);
		
		ft_putstr_fd(msg_full, STDERR_FILENO);
		//ft_putstr_fd("\n", STDERR_FILENO);
		
	}
	free(msg_full);
	return (0);

}
