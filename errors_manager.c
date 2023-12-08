#include "minishell.h"

int	errors_manager(int action, int code, char *msg, char *arg)
{
	static int	exit_code;
	char		*msg_full;
	int			msg_len;

	msg_full = 0;
	if (action == GET_CODE)
		return (exit_code);
	else if (action == SET_CODE)
		exit_code = code;
	else if (action == PRINT)
	{
		if (!msg)
			return (-1);
		msg_len = ft_strlen(msg) + ft_strlen(arg) + 3;
		msg_full = malloc(msg_len);
		if (!msg_full)
			return (-1);
		ft_strcpy(msg_full, arg);
		ft_strcat(msg_full, ": ");
		ft_strcat(msg_full, msg);
		ft_putstr_fd(msg_full, STDERR_FILENO);
	}
	free(msg_full);
	return (0);
}
