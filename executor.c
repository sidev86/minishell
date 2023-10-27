#include "minishell.h"

extern int e_code;

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
}

void ft_exec_systemcmd(t_command **cmd, char **envp)
{
    //printf("System Command Exec\n");
    char *path = getenv("PATH");
    char **dirs;
    int i;

    i = 0; 
    dirs = ft_split(path, ':');
    while (dirs[i])
    {
        path = ft_strjoin(dirs[i], "/");
        path = ft_strjoin(path, (*cmd)->argv[0]);
        //printf("path= %s\n", path);
        
        execve(path, (*cmd)->argv, envp);
        i++;
    }
    printf("Command not found\n");
}

void ft_execute(t_command **cmd, t_env_vars **env_list, char **envp)
{
    int status;
    pid_t pid;

    pid = fork();
    //printf("env list = %s\n", (*env_list)->env_str);
    //printf("parola chiave= %s\n", (*cmd)->argv[0]);
    if (pid < 0)
        perror("Fork() error");
    else if (pid == 0) //Child Process
    {
        //printf("childpid = %d\n", childPid);
        //printf("parola chiave child= %s\n", (*cmd)->argv[0]);
        //printf("env list = %s\n", (*env_list)->env_str);
        if ((*cmd)->is_builtin)
            ft_exec_builtin(cmd, &env_list);
        else
            ft_exec_systemcmd(cmd, envp);
    
        //printf("child process end\n");
	//exit(0);
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


