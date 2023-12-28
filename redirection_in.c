/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:29:52 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:29:54 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redir_input(char *filename)
{
	int	original_fd;
	int	file;

	original_fd = dup(STDIN_FILENO);
	if (filename)
	{
		file = open(filename, O_RDONLY);
		if (file == -1)
		{
			errors_manager(SET_CODE, 1, NULL, NULL);
			errors_manager(PRINT, 1, "Can't open or create file\n", filename);
			return (-1);
		}
		dup2(file, STDIN_FILENO);
		close(file);
	}
	return (original_fd);
}

static void	handle_redirection(t_command **cmd, int *i, int *num_redir)
{
	(*cmd)->redir_in = 1;
	(*num_redir)++;
	free((*cmd)->argv[*i]);
	(*cmd)->argv[*i] = NULL;
	if ((*cmd)->argv[*i + 1])
	{
		free((*cmd)->argv[*i + 1]);
		(*cmd)->argv[*i + 1] = NULL;
	}
	(*i)++;
}

static void	ft_empty_in_other(t_command **cmd)
{
	int	i;
	int	last_redir;
	int	num_redir;

	i = 0;
	num_redir = 0;
	last_redir = (*cmd)->num_redirs - 1;
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if (!ft_strcmp((*cmd)->argv[i], "<") || !ft_strcmp((*cmd)->argv[i],
					"<<"))
			{
				handle_redirection(cmd, &i, &num_redir);
				if (num_redir == last_redir)
					break ;
			}
		}
		i++;
	}
}

static void	handle_input_redirection(t_command **cmd, t_env_vars **env_list, int *fd_stdin, int i)
{
	if (!ft_strcmp((*cmd)->argv[i], "<"))
	{
		*fd_stdin = ft_redir_input((*cmd)->argv[i + 1]);
	}
	else if (!ft_strcmp((*cmd)->argv[i], "<<"))
	{
		//printf("heredoc\n");
		ft_heredoc(cmd, env_list);
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
		ft_empty_in_other(cmd);
	}
}

void	ft_check_input_redirs(t_command **cmd, t_env_vars **env_list)
{
	int	i;
	int	fd_stdin;

	fd_stdin = 0;
	i = 0;
	(*cmd)->num_redirs = ft_get_in_redirections(cmd);
	if ((*cmd)->num_redirs > 0)
	{
		(*cmd)->redir_in = 1;
		i = ft_last_in_redir(cmd);
	}	
	if ((*cmd)->argv[i])
	{
		if (!ft_strcmp((*cmd)->argv[i], "<") || !ft_strcmp((*cmd)->argv[i],
				"<<"))
		{
			handle_input_redirection(cmd, env_list, &fd_stdin, i);
		}
	}
	i++;
	(*cmd)->fd_stdinput = fd_stdin;
}
