#include "minishell.h"


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
    if (!ft_strcmp((*cmd)->argv[0], "echo"))
        ft_echo(cmd);
    else if (!ft_strcmp((*cmd)->argv[0], "cd"))
        ft_cd(cmd);
    else if (!ft_strcmp((*cmd)->argv[0], "pwd"))
        ft_pwd();
    else if (!ft_strcmp((*cmd)->argv[0], "export"))
    	ft_export(cmd, env_list);
    else if (!ft_strcmp((*cmd)->argv[0], "unset"))
        ft_unset(cmd, env_list);
    else if (!ft_strcmp((*cmd)->argv[0], "env"))
        ft_env(env_list);
    else
    {
        errors_manager(SET_CODE, 127, NULL, NULL);
        errors_manager(PRINT,127,"Command not found", "Error");
    }
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
				errors_manager(SET_CODE, 100, NULL, NULL);
				if (execve(path, (*cmd)->argv, envp) == -1)
				{
        				errors_manager(PRINT,126,"Execution error\n", "Error");
        				exit (126);
				}
				
					exit(0);
			}
			i++;
		}
	}
	errors_manager(PRINT,127,"Command not found\n", (*cmd)->argv[0]);
	exit (127);
    }
    else 
    {
    	path = (*cmd)->argv[0];
    	
    	if (access(path, F_OK | X_OK) == 0)
	{
		(*cmd)->argv[0] = ft_get_cmdname((*cmd)->argv[0]);
		if (execve(path, (*cmd)->argv, envp) == -1)
		{
		 	errors_manager(SET_CODE, 127, NULL, NULL);
			errors_manager(PRINT,127,"Execution error", "Error");
		}
			exit (0);
	}	
	if ((*cmd)->argv[0][0] == '.' && (*cmd)->argv[0][1] == '/')
	{
		errors_manager(PRINT,126,"Executable not found\n", (*cmd)->argv[0]);
		exit (126);
	}
	errors_manager(PRINT,127,"Commando not found\n", (*cmd)->argv[0]);
	exit (127);
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
	if (curr_cmd->num_cmds > 1 || (curr_cmd->num_cmds == 1 && !curr_cmd->is_builtin))
	{
		while (curr_cmd)
		{
			if (curr_cmd->next)
				pipe(fd_new);
			pid = fork(); 
			if (pid == 0)
			{
				errors_manager(SET_CODE, 0, NULL, NULL);
				ft_check_output_redirs(&curr_cmd);
				ft_check_input_redirs(&curr_cmd);
				if (errors_manager(GET_CODE, 0, NULL, NULL) == 1)
					exit (1);
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
				exit(0);	
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
			if (WIFEXITED(status)) 
			{
			     errors_manager(SET_CODE, WEXITSTATUS(status), NULL, NULL);
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


