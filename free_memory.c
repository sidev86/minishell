/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <sibrahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:40:47 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/26 12:12:50 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_list(t_env_vars **env_list)
{
	t_env_vars	*curr_env;
	t_env_vars	*next_env;

	curr_env = *env_list;
	while (curr_env)
	{
		next_env = curr_env->next;
		if (curr_env->var)
			free(curr_env->var);
		if (curr_env->value)
			free(curr_env->value);
		if (curr_env->env_str)
			free(curr_env->env_str);
		free(curr_env);
		curr_env = next_env;
	}
	*env_list = NULL;
}

void	ft_free_all_commands(t_command **cmd)
{
	t_command	*curr_cmd;
	t_command	*next_cmd;
	int			i;

	i = 0;
	curr_cmd = *cmd;
	while (curr_cmd->prev)
		curr_cmd = curr_cmd->prev;
	while (curr_cmd)
	{
		i = 0;
		next_cmd = curr_cmd->next;
		while (i < curr_cmd->num_tokens)
			free((curr_cmd)->argv[i++]);
		free(curr_cmd->argv);
		free(curr_cmd);
		curr_cmd = next_cmd;
	}
	*cmd = NULL;
}

void	ft_free_heredoc(t_command **cmd, char **dirs, t_env_vars **env_list,
		int signal)
{
	int	i;

	i = 0;
	while (i < (*cmd)->heredoc_counter)
		free((*cmd)->end_tokens[i++]);
	i = 0;
	while (i < (*cmd)->lines_heredoc)
		free((*cmd)->heredoc_text[i++]);
	i = 0;
	if (dirs)
	{
		while (dirs[i])
			free(dirs[i++]);
		free(dirs);
	}
	free((*cmd)->heredoc_text);
	free((*cmd)->end_tokens);
	ft_free_all_commands(cmd);
	ft_free_env_list(env_list);
	if (signal)
		exit(130);
	else
		exit(0);
}

void	ft_free_tokens(t_tokens *cmd_line, int total_tokens)
{
	int	i;

	i = 0;
	while (i < total_tokens)
	{
		free(cmd_line[i].token);
		i++;
	}
	free(cmd_line);
}

void	ft_free_cmd(t_command **cmd)
{
	int	i;

	i = 0;
	while (i < (*cmd)->num_tokens)
		free((*cmd)->argv[i++]);
	free((*cmd)->argv);
	free(*cmd);
}
