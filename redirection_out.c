#include "minishell.h"
#include <fcntl.h>

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

void	ft_empty_out_redir(t_command **cmd, int i, int *num_redir)
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
			free((*cmd)->argv[i+1]);
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

void	ft_check_output_redirs(t_command **cmd)
{
	int	i;
	int	fd_stdout;

	fd_stdout = 1;
	i = 0;
	(*cmd)->num_redirs = ft_get_out_redirections(cmd);
	if ((*cmd)->num_redirs > 0)
		i = ft_last_out_redir(cmd);
	if ((*cmd)->argv[i])
	{
		if (!ft_strcmp((*cmd)->argv[i], ">") || !ft_strcmp((*cmd)->argv[i],
				">>"))
		{
			(*cmd)->redir_out = 1;
			if (!ft_strcmp((*cmd)->argv[i], ">"))
				fd_stdout = ft_redir_output_overwrite((*cmd)->argv[i + 1]);
			else if (!ft_strcmp((*cmd)->argv[i], ">>"))
				fd_stdout = ft_redir_output_append((*cmd)->argv[i + 1]);
			free((*cmd)->argv[i]);
			(*cmd)->argv[i] = NULL;
			if ((*cmd)->argv[i + 1])
			{
				free((*cmd)->argv[i+1]);
				(*cmd)->argv[i + 1] = NULL;
			}
			if ((*cmd)->num_redirs > 1)
				ft_empty_out_other(cmd);
		}
	}
	i++;
	(*cmd)->fd_terminal = fd_stdout;
}
