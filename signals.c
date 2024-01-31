/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <sibrahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:44:09 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/26 12:12:31 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_sigint_checker(SET_CODE, 1);
		errors_manager(SET_CODE, 130, NULL, NULL);
	}
}

int	ft_sigint_checker(int action, int code)
{
	static int	sigint_heredoc;

	if (action == SET_CODE)
		sigint_heredoc = code;
	else if (action == GET_CODE)
		return (sigint_heredoc);
	return (sigint_heredoc);
}

void	ft_check_heredoc_signal(t_command **cmd, t_env_vars **env_list)
{
	cmd = cmd;
	env_list = env_list;
	if (ft_sigint_checker(GET_CODE, 0) == 1)
	{
		ft_sigint_checker(SET_CODE, 0);
		ft_free_heredoc(cmd, 0, env_list, 1);
	}
}
