#include "minishell.h"

extern int e_code;

char *ft_get_cmdname(char *str)
{
	int	i; 
	int	j;
	char	*cmd;
	i = 0; 
	while(str[i])
		i++;
	i--;
	j = i; 
	while(str[j] != '/')
		j--;
	j++;
	cmd = ft_substr(str, j, i - j + 1);
	return (cmd);
}


int ft_get_total_cmds(t_command **cmd)
{
	int total; 
	
	total = 0;
	while(*cmd)
	{
		total++;
		(*cmd) = (*cmd)->next;
	}
	
	return (total);
}

void ft_exec_builtin(t_command** cmd, t_env_vars ***env_list)
{
    //printf("variabile env = %s\n", (**env_list)->env_str);
    if (!ft_strcmp((*cmd)->argv[0], "echo"))
        e_code = ft_echo(cmd);
    else if (!ft_strcmp((*cmd)->argv[0], "cd"))
        e_code = ft_cd(cmd);
    else if (!ft_strcmp((*cmd)->argv[0], "pwd"))
        e_code = ft_pwd();
    else if (!ft_strcmp((*cmd)->argv[0], "export"))
        e_code = ft_export(cmd, env_list);
    else if (!ft_strcmp((*cmd)->argv[0], "unset"))
        e_code = ft_unset(cmd, env_list);
    else if (!ft_strcmp((*cmd)->argv[0], "env"))
        e_code = ft_env(env_list);
    //else if (!strcmp((*cmd)->argv[0], "exit"))
    //    ft_exit(cmd);
    else
        printf("Error. Commando not found\n");
    //printf("exit code = %d\n", e_code);
}

char *ft_get_path(t_env_vars **env_list)
{
	t_env_vars	*curr;
	curr = *env_list;
	
	while(curr)
	{
		if (!ft_strcmp(curr->var, "PATH"))
			return (curr->value);
		if (curr->next)
			curr = curr->next;
		else
			break ;
	}
	return(NULL);
}

void ft_exec_systemcmd(t_command **cmd, char **envp, t_env_vars **env_list)
{
    char *path = ft_get_path(env_list);
    char **dirs;
    int i;

    i = 0; 
 
    if (!ft_strchr((*cmd)->argv[0], '/'))
    {
    
	if (path)
	{
		dirs = ft_split(path, ':');
		while (dirs[i])
		{
			path = ft_strjoin(dirs[i], "/");
			path = ft_strjoin(path, (*cmd)->argv[0]);
			if (access(path, F_OK | X_OK) == 0)
			{
				if (execve(path, (*cmd)->argv, envp) == -1)
					e_code = 127;
			}
			i++;
		}
	}
	ft_putstr_fd("command not found\n", STDERR_FILENO);
    }
    else 
    {
    	path = (*cmd)->argv[0];
    	(*cmd)->argv[0] = ft_get_cmdname((*cmd)->argv[0]);
    	if (execve(path, (*cmd)->argv, envp) == -1)
		e_code = 127;
    	ft_putstr_fd("command not found\n", STDERR_FILENO);
    }
}

void ft_handle_quotes_alltokens(t_command **cmd)
{
	int i; 
	
	i = 0;
	
	while (i < (*cmd)->argc)
	{
		if ((*cmd)->argv[i])
		{
			(*cmd)->argv[i] = handle_quotes((*cmd)->argv[i]);
		}
		i++;
	}
}

void ft_execute(t_command **cmd, t_env_vars **env_list, char **envp)
{
	int status;
	pid_t pid;
	int fd_old[2];
	int fd_new[2];
	int i = 0;
	t_command *curr_cmd; 
	
	curr_cmd = *cmd;
	if (curr_cmd->num_cmds > 1)
	{
		while (curr_cmd)
		{
			if (curr_cmd->next)
				pipe(fd_new);
			pid = fork(); 
			if (pid == 0)
			{
				ft_check_output_redirs(&curr_cmd);
				ft_check_input_redirs(&curr_cmd);
				ft_handle_quotes_alltokens(&curr_cmd);
				if (curr_cmd->prev && !curr_cmd->redir_in)
				{
					dup2(fd_old[0], STDIN_FILENO);
					close(fd_old[0]);
					close(fd_old[1]);
				}
				if (curr_cmd->next && !curr_cmd->redir_out)
				{
					close(fd_new[0]);
					dup2(fd_new[1], STDOUT_FILENO);
					close(fd_new[1]);
				
				}
				if (curr_cmd->argv[0] && !curr_cmd->is_builtin)
					ft_exec_systemcmd(&curr_cmd, envp, env_list);
				else if (curr_cmd->argv[0] && curr_cmd->is_builtin)
					ft_exec_builtin(&curr_cmd, &env_list);
				exit(1);	
			}
			else
			{
				if (curr_cmd->prev)
				{
					close(fd_old[0]);
					close(fd_old[1]);
				}
				if (curr_cmd->next)
				{
					fd_old[0] = fd_new[0];
					fd_old[1] = fd_new[1];
				}
				if ((*cmd)->fd_terminal != -1 && (*cmd)->redir_out)
					dup2((*cmd)->fd_terminal, STDOUT_FILENO);
				if ((*cmd)->fd_stdinput != -1 && (*cmd)->redir_in)
					dup2((*cmd)->fd_stdinput, STDIN_FILENO);
			}
			curr_cmd = curr_cmd->next;
		}
		if ((*cmd)->num_cmds > 1)
		{
			close(fd_old[0]);
			close(fd_old[1]);
		}
		
		while (i < (*cmd)->num_cmds)
		{
			wait(&status);
			if (WIFEXITED(status)) {
			    e_code = WEXITSTATUS(status);
			}
			i++;
		
		}
	}
	
	else
	{
		ft_check_output_redirs(&curr_cmd);
		ft_check_input_redirs(&curr_cmd);
		ft_handle_quotes_alltokens(&curr_cmd);
		
		if (curr_cmd->argv[0] && curr_cmd->is_builtin)
			ft_exec_builtin(cmd, &env_list);
		else if (curr_cmd->argv[0] && !curr_cmd->is_builtin)
			ft_exec_systemcmd(&curr_cmd, envp, env_list);
		if ((*cmd)->fd_terminal != -1)
		{
			dup2((*cmd)->fd_terminal, STDOUT_FILENO);
		}
		if ((*cmd)->fd_stdinput != -1)
		{
			dup2((*cmd)->fd_stdinput, STDIN_FILENO);
		}	
	}	
}


