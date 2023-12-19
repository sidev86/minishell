/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:30:31 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:30:33 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_out_redirections(t_command **cmd)
{
	int	i;
	int	redirs;

	i = 0;
	redirs = 0;
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if ((!ft_strcmp((*cmd)->argv[i], ">") || !ft_strcmp((*cmd)->argv[i],
						">>")) && (*cmd)->argv[i])
				redirs++;
		}
		i++;
	}
	return (redirs);
}

static void	handle_output_redirection(t_command **cmd, int *fd_stdout, int i)
{
	(*cmd)->redir_out = 1;
	if (!ft_strcmp((*cmd)->argv[i], ">"))
	{
		*fd_stdout = ft_redir_output_overwrite((*cmd)->argv[i + 1]);
	}
	else if (!ft_strcmp((*cmd)->argv[i], ">>"))
	{
		*fd_stdout = ft_redir_output_append((*cmd)->argv[i + 1]);
	}
	free((*cmd)->argv[i]);
	(*cmd)->argv[i] = NULL;
	if ((*cmd)->argv[i + 1])
	{
		free((*cmd)->argv[i + 1]);
		(*cmd)->argv[i + 1] = NULL;
	}
	if ((*cmd)->num_redirs > 1)
	{
		ft_empty_out_other(cmd);
	}
}

void	ft_check_output_redirs(t_command **cmd)
{
	int	i;
	int	fd_stdout;

	fd_stdout = 1;
	i = 0;
	(*cmd)->num_redirs = ft_get_out_redirections(cmd);
	if ((*cmd)->num_redirs > 0)
	{
		(*cmd)->redir_out = 1;
		i = ft_last_out_redir(cmd);
	}
	if ((*cmd)->argv[i])
	{
		if (!ft_strcmp((*cmd)->argv[i], ">") || !ft_strcmp((*cmd)->argv[i],
				">>"))
		{
			handle_output_redirection(cmd, &fd_stdout, i);
		}
	}
	i++;
	(*cmd)->fd_terminal = fd_stdout;
}
