/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:30:22 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:30:24 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last_out_redir(t_command **cmd)
{
	int	i;
	int	redir_num;

	i = 0;
	redir_num = 0;
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if (!ft_strcmp((*cmd)->argv[i], ">") || !ft_strcmp((*cmd)->argv[i],
					">>"))
				redir_num++;
		}
		if (redir_num == (*cmd)->num_redirs)
			break ;
		i++;
	}
	return (i);
}

int	ft_redir_output_overwrite(char *filename)
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

int	ft_redir_output_append(char *filename)
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

static void	ft_empty_out_redir(t_command **cmd, int i, int *num_redir)
{
	int	file;

	if (!ft_strcmp((*cmd)->argv[i], ">"))
	{
		file = open((*cmd)->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file == -1)
		{
			errors_manager(SET_CODE, 1, NULL, NULL);
			errors_manager(PRINT, 1, "Can't open or create file\n", "Error");
			return ;
		}
		close(file);
	}
	if (!ft_strcmp((*cmd)->argv[i], ">") || !ft_strcmp((*cmd)->argv[i], ">>"))
	{
		(*num_redir)++;
		free((*cmd)->argv[i]);
		(*cmd)->argv[i] = NULL;
		if ((*cmd)->argv[i + 1])
		{
			free((*cmd)->argv[i + 1]);
			(*cmd)->argv[i + 1] = NULL;
		}
		i++;
	}
}

void	ft_empty_out_other(t_command **cmd)
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
			ft_empty_out_redir(cmd, i, &num_redir);
		}
		if (num_redir == last_redir)
			break ;
		i++;
	}
}
