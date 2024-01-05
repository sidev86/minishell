/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:29:36 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:29:37 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_num_cmds(t_tokens *cmd_line, int num_tokens)
{
	int	i;
	int	num_cmds;

	i = 0;
	num_cmds = 0;
	if (cmd_line[i].token)
		num_cmds++;
	while (i < num_tokens)
	{
		if (!ft_strcmp(cmd_line[i].token, "|"))
			num_cmds++;
		i++;
	}
	return (num_cmds);
}

int	ft_get_tokens_in_cmd(t_tokens *cmd_line, int index, int total_tokens)
{
	int	tokens;

	tokens = 0;
	if (cmd_line[index].token[0] == '|')
	{
		errors_manager(SET_CODE, 2, NULL, NULL);
		errors_manager(PRINT, 1, "Syntax error near unexpected token '|'\n", "Error");
		return (-1);
	}
	while (index < total_tokens)
	{
		if (!ft_strchr(cmd_line[index].token, '|')
			|| (ft_strchr(cmd_line[index].token, '|')
				&& ft_strlen(cmd_line[index].token) > 1))
		{
			tokens++;
			index++;
		}
		else
			break ;
	}
	return (tokens);
}

int	ft_put_tokens_in_cmd(t_command **curr_cmd, t_tokens *cmd_line,
		int arg_index)
{
	int	i;

	i = 0;
	while (i < (*curr_cmd)->num_tokens)
	{
		(*curr_cmd)->argv[i] = ft_substr(cmd_line[arg_index + i].token, 0,
				ft_strlen(cmd_line[arg_index + i].token));
		if (!ft_strcmp((*curr_cmd)->argv[i], "<<"))
			(*curr_cmd)->has_heredoc = 1;
		
		i++;
	}
	return (i);
}
