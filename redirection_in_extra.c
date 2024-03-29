/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:19 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:43:20 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_ifheredoc(t_command **cmd, int *i)
{
	if (!ft_strcmp((*cmd)->argv[*i], "<<"))
	{
		(*cmd)->heredoc_counter++;
		(*cmd)->end_tokens = realloc((*cmd)->end_tokens, sizeof(char *)
				* (*cmd)->heredoc_counter);
		if (!(*cmd)->end_tokens)
		{
			ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
			exit(1);
		}
		(*cmd)->end_tokens[((*cmd)->heredoc_counter)
			- 1] = ft_strdup((*cmd)->argv[*i + 1]);
	}
}

int	ft_get_in_redirections(t_command **cmd)
{
	int	i;
	int	redirs;

	i = 0;
	redirs = 0;
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if (!ft_strcmp((*cmd)->argv[i], "<") || !ft_strcmp((*cmd)->argv[i],
					"<<"))
			{
				redirs++;
				ft_ifheredoc(cmd, &i);
			}
		}
		i++;
	}
	return (redirs);
}

int	ft_last_in_redir(t_command **cmd)
{
	int	i;
	int	redir_num;

	i = 0;
	redir_num = 0;
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if (!ft_strcmp((*cmd)->argv[i], "<") || !ft_strcmp((*cmd)->argv[i],
					"<<"))
				redir_num++;
		}
		if (redir_num == (*cmd)->num_redirs)
			break ;
		i++;
	}
	return (i);
}
