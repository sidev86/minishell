#include "minishell.h"


void ft_exec_builtin(t_command** cmd, t_env_vars ***env_list)
{
    //printf("variabile env = %s\n", (**env_list)->env_str);
    if (!strcmp((*cmd)->argv[0], "echo"))
        ft_echo(cmd);
    else if (!strcmp((*cmd)->argv[0], "cd"))
        ft_cd(cmd);
    else if (!strcmp((*cmd)->argv[0], "pwd"))
        ft_pwd();
    else if (!strcmp((*cmd)->argv[0], "export"))
        ft_export(cmd, env_list);
    else if (!strcmp((*cmd)->argv[0], "unset"))
        ft_unset(cmd, env_list);
    else if (!strcmp((*cmd)->argv[0], "env"))
        ft_env(env_list);
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
    pid_t childPid;
    int status;
    childPid = fork();
    //printf("env list = %s\n", (*env_list)->env_str);
    //printf("parola chiave= %s\n", (*cmd)->argv[0]);
    if (childPid < 0)
        perror("Fork() error");
    else if (childPid == 0) //Child Process
    {
        //printf("childpid = %d\n", childPid);
        //printf("parola chiave child= %s\n", (*cmd)->argv[0]);
        printf("env list = %s\n", (*env_list)->env_str);
        if ((*cmd)->is_builtin)
            ft_exec_builtin(cmd, &env_list);
        else
            ft_exec_systemcmd(cmd, envp);
    
        //exit(0);
        
    }
    else //Parent Process 
    {
        wait(&status);
    }
}
