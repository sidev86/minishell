/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:05:45 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/26 15:05:47 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_in_child(t_command **curr_cmd, int *fd_pipe, t_env_vars **env_list,
		char **envp)
{
	if (!ft_strcmp((*curr_cmd)->argv[0], "\"\"")
		|| !ft_strcmp((*curr_cmd)->argv[0], "\'\'"))
	{
		free((*curr_cmd)->argv[0]);
		(*curr_cmd)->argv[0] = ft_strdup("\"\'\'\"");
	}
	ft_execute_in_child(curr_cmd, fd_pipe, env_list, envp);
}
