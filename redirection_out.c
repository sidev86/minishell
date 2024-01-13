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

static int	ft_redir_output_overwrite(char *filename)
{
	int	original_fd;
	int	file;

	original_fd = dup(STDOUT_FILENO);
	if (filename)
	{
		file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file == -1)
		{
			errors_manager(SET_CODE, 1, NULL, NULL);
			errors_manager(PRINT, 1, "Can't open or create file\n", filename);
			return (-1);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	return (original_fd);
}

static int	ft_redir_output_append(char *filename)
{
	int	original_fd;
	int	file;

	original_fd = dup(STDOUT_FILENO);
	if (filename)
	{
		file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (file == -1)
		{
			errors_manager(SET_CODE, 1, NULL, NULL);
			errors_manager(PRINT, 1, "Can't open or create file\n", filename);
			return (-1);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	return (original_fd);
}

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

static void	handle_output_redirection(t_command **cmd, int *fd_stdout, int i, t_env_vars **env_list)
{
	(*cmd)->redir_out = 1;
	if (!ft_strcmp((*cmd)->argv[i], ">"))
	{
		ft_handle_quotes_single_token(cmd, env_list, i + 1);
		*fd_stdout = ft_redir_output_overwrite((*cmd)->argv[i + 1]);
	}
	else if (!ft_strcmp((*cmd)->argv[i], ">>"))
	{
		ft_handle_quotes_single_token(cmd, env_list, i + 1);
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

void	ft_check_output_redirs(t_command **cmd, t_env_vars **env_list)
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
			handle_output_redirection(cmd, &fd_stdout, i, env_list);
		}
	}
	i++;
	(*cmd)->fd_terminal = fd_stdout;
}
