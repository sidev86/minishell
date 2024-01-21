#include "minishell.h"

int	check_var_validity(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && ((arg[i] >= '0' && arg[i] <= '9') || arg[i] == '='))
			return (1);
		if (!ft_is_a_valid_character(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_redir_to_pipe(t_command **curr_cmd, int *fd_pipe)
{
	if ((*curr_cmd)->prev && !(*curr_cmd)->redir_in)
	{
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	if ((*curr_cmd)->next && !(*curr_cmd)->redir_out)
	{
		close(fd_pipe[2]);
		dup2(fd_pipe[3], STDOUT_FILENO);
		close(fd_pipe[3]);
	}
}

void	allocate_heredoc_output(char *input_line, char **output)
{
	
	if (input_line[0])
		*output = (char *)malloc(ft_strlen(input_line) * 1000);
	else
		*output = (char *)malloc(ft_strlen(input_line) + 1);
	
	if (!(*output))
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
}


void	allocate_heredoc_text(t_command **cmd, int line_count)
{
	if (!(*cmd)->heredoc_text)
		(*cmd)->heredoc_text = (char **)malloc((line_count) * sizeof(char *));
	else
		(*cmd)->heredoc_text = (char **)ft_realloc((*cmd)->heredoc_text,((line_count) - 1) * sizeof(char *), (line_count) * sizeof(char *));
	if (!(*cmd)->heredoc_text)
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
}

void	ft_free_in_child_exec(t_command **curr_cmd, t_env_vars **env_list)
{
	if ((*curr_cmd)->has_heredoc)
			ft_free_heredoc(curr_cmd, 0, env_list);
	else
	{
		ft_free_all_commands(curr_cmd);
		ft_free_env_list(env_list);
	}
}

