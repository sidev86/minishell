#include "minishell.h"
#include <fcntl.h>

int	ft_redir_input(char *filename)
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

void	ft_empty_in_other(t_command **cmd)
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
				(*cmd)->redir_in = 1;
				num_redir++;
				free((*cmd)->argv[i]);
				(*cmd)->argv[i] = NULL;
				if ((*cmd)->argv[i + 1])
				{
					free((*cmd)->argv[i+1]);
					(*cmd)->argv[i + 1] = NULL;
				}
				i++;
			}
			if (num_redir == last_redir)
				break ;
		}
		i++;
	}
}

void	ft_check_input_redirs(t_command **cmd)
{
	int	i;
	int	fd_stdin;

	fd_stdin = 0;
	i = 0;
	(*cmd)->num_redirs = ft_get_in_redirections(cmd);
	if ((*cmd)->num_redirs > 0)
		i = ft_last_in_redir(cmd);
	if ((*cmd)->argv[i])
	{
		if (!ft_strcmp((*cmd)->argv[i], "<") || !ft_strcmp((*cmd)->argv[i],
				"<<"))
		{
			if (!ft_strcmp((*cmd)->argv[i], "<"))
				fd_stdin = ft_redir_input((*cmd)->argv[i + 1]);
			else if (!ft_strcmp((*cmd)->argv[i], "<<"))
				ft_heredoc(cmd);
			free((*cmd)->argv[i]);
			(*cmd)->argv[i] = NULL;
			if ((*cmd)->argv[i + 1])
			{
				free((*cmd)->argv[i+1]);
				(*cmd)->argv[i + 1] = NULL;
			}
			if ((*cmd)->num_redirs > 1)
				ft_empty_in_other(cmd);
		}
	}
	i++;
	(*cmd)->fd_stdinput = fd_stdin;
}
