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


void ft_exec_builtin(t_command** cmd, t_env_vars ***env_list)
{
    //printf("variabile env = %s\n", (**env_list)->env_str);
    if (!strcmp((*cmd)->argv[0], "echo"))
        e_code = ft_echo(cmd);
    else if (!strcmp((*cmd)->argv[0], "cd"))
        e_code = ft_cd(cmd);
    else if (!strcmp((*cmd)->argv[0], "pwd"))
        e_code = ft_pwd();
    else if (!strcmp((*cmd)->argv[0], "export"))
        e_code = ft_export(cmd, env_list);
    else if (!strcmp((*cmd)->argv[0], "unset"))
        e_code = ft_unset(cmd, env_list);
    else if (!strcmp((*cmd)->argv[0], "env"))
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
		if (!strcmp(curr->var, "PATH"))
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
    //printf("env_list var is %s\n", (*env_list)->var);
    //printf("env_list value is %s\n", (*env_list)->value);
    //printf("path = %s\n", path);
    if (!ft_strchr((*cmd)->argv[0], '/'))
    {
	if (path)
	{
		dirs = ft_split(path, ':');
		while (dirs[i])
		{
			path = ft_strjoin(dirs[i], "/");
			path = ft_strjoin(path, (*cmd)->argv[0]);
			//printf("path= %s\n", path);
			//printf("cmd argv = %s\n", (*cmd)->argv);
			execve(path, (*cmd)->argv, envp);
			i++;
		}
	}
	printf("Command not found\n");
    }
    else 
    {
    	path = (*cmd)->argv[0];
    	(*cmd)->argv[0] = ft_get_cmdname((*cmd)->argv[0]);
    	//printf("command name = %s\n", (*cmd)->argv[0]);
    	execve(path, (*cmd)->argv, envp);
    	printf("Command not found\n");
    }
}

void ft_execute(t_command **cmd, t_env_vars **env_list, char **envp)
{
	int status;
	pid_t pid;


	//printf("executionn\n");
	if (!(*cmd)->is_builtin)
	{
		pid = fork();
		//printf("env list = %s\n", (*env_list)->env_str);
		//printf("parola chiave= %s\n", (*cmd)->argv[0]);
		if (pid < 0)
			perror("Fork() error");
		else if (pid == 0) //Child Process
		{
			ft_check_for_redirections(cmd);
			//printf("childpid = %d\n", childPid);
			//printf("parola chiave child= %s\n", (*cmd)->argv[0]);
			//printf("env list = %s\n", (*env_list)->env_str);
			ft_exec_systemcmd(cmd, envp, env_list);
			//printf("child process end\n");
			exit(0);
			//return ;
		}
		else //Parent Process 
		{
			//if (WIFEXITED(status)) {
			// Il processo figlio è terminato correttamente
			//int exit_code = WEXITSTATUS(status);
			//printf("Codice di uscita: %d\n", exit_code);
			//}
			wait(&status); // Attendere il processo figlio
			if (WIFEXITED(status)) {
			    WEXITSTATUS(status);
			    //printf("Codice di uscita del processo figlio: %d\n", exit_code);
			}
			//}
			// exit_code contiene il codice di uscita del comando

		}
	}
	else
	{
		ft_check_for_redirections(cmd);
		ft_exec_builtin(cmd, &env_list);
		if ((*cmd)->fd_terminal != -1)
		{
			dup2((*cmd)->fd_terminal, STDOUT_FILENO);
		}
		
	}	
}


