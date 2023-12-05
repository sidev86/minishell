#include "minishell.h"

void ft_execute_in_child(t_command **curr_cmd, int *fd_pipe, t_env_vars **env_list, char **envp)
{
	errors_manager(SET_CODE, 0, NULL, NULL);
	ft_check_input_redirs(curr_cmd);
	ft_check_output_redirs(curr_cmd);
	if (errors_manager(GET_CODE, 0, NULL, NULL) == 1)
		exit(1);
	ft_handle_quotes_alltokens(curr_cmd);
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
	if ((*curr_cmd)->argv[0] && !(*curr_cmd)->is_builtin)
		ft_exec_systemcmd(curr_cmd, envp, env_list);
	else if ((*curr_cmd)->argv[0] && (*curr_cmd)->is_builtin)
		ft_exec_builtin(curr_cmd, &env_list);
	exit(0);
}

void ft_after_child_exec(t_command **curr_cmd, t_command **cmd, int *fd_pipe)
{
	if ((*curr_cmd)->prev)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	if ((*curr_cmd)->next)
	{
		fd_pipe[0] = fd_pipe[2];
		fd_pipe[1] = fd_pipe[3];
	}
	if ((*cmd)->fd_terminal != -1 && (*cmd)->redir_out)
		dup2((*cmd)->fd_terminal, STDOUT_FILENO);
	if ((*cmd)->fd_stdinput != -1 && (*cmd)->redir_in)
		dup2((*cmd)->fd_stdinput, STDIN_FILENO);
}

void ft_wait_child_termination(t_command **cmd, int status, int *fd_pipe)
{
	int i;
	
	i = 0;
	if ((*cmd)->num_cmds > 1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	while (i < (*cmd)->num_cmds)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			errors_manager(SET_CODE, WEXITSTATUS(status), NULL, NULL);
		}
		i++;
	}
}

void  ft_exec_single_builtin(t_command **curr_cmd, t_command **cmd, t_env_vars **env_list)
{
	ft_check_output_redirs(curr_cmd);
	ft_check_input_redirs(curr_cmd);
	ft_handle_quotes_alltokens(curr_cmd);
	if ((*curr_cmd)->argv[0] && (*curr_cmd)->is_builtin)
		ft_exec_builtin(curr_cmd, &env_list);
	if ((*cmd)->fd_terminal != -1)
	{
		dup2((*cmd)->fd_terminal, STDOUT_FILENO);
	}
	if ((*cmd)->fd_stdinput != -1)
	{
		dup2((*cmd)->fd_stdinput, STDIN_FILENO);
	}
}

void	ft_execute(t_command **cmd, t_env_vars **env_list, char **envp)
{
	int			status;
	int			fd_pipe[4];	
	pid_t		pid;
	t_command	*curr_cmd;
	
	status = 0;
	curr_cmd = *cmd;
	if (curr_cmd->num_cmds > 1 || (curr_cmd->num_cmds == 1
			&& !curr_cmd->is_builtin))
	{
		while (curr_cmd)
		{
			if (curr_cmd->next)
				pipe(&fd_pipe[2]);
			pid = fork();
			if (pid == 0)
				ft_execute_in_child(&curr_cmd, fd_pipe, env_list, envp);
			else
				ft_after_child_exec(&curr_cmd, cmd, fd_pipe);
			curr_cmd = curr_cmd->next;
		}
		ft_wait_child_termination(cmd, status, fd_pipe);	
	}
	else
		ft_exec_single_builtin(&curr_cmd, cmd, env_list);
}
