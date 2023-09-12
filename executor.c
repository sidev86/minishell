#include "minishell.h"


void ft_exec_builtin(t_command** cmd, t_env_vars **env_list)
{
    printf("variavbile env = %s\n", (*env_list)->env_str);
    if (!strcmp((*cmd)->argv[0], "echo"))
        ft_echo(cmd);
    else if (!strcmp((*cmd)->argv[0], "cd"))
        ft_cd(cmd);
    else if (!strcmp((*cmd)->argv[0], "pwd"))
        ft_pwd(cmd);
    else if (!strcmp((*cmd)->argv[0], "export"))
        ft_export(cmd, env_list);
    else if (!strcmp((*cmd)->argv[0], "unset"))
        ft_unset(cmd);
    else if (!strcmp((*cmd)->argv[0], "env"))
        ft_env(cmd, env_list);
    else if (!strcmp((*cmd)->argv[0], "exit"))
        ft_exit(cmd);
    else
        printf("Error. Commando not found\n");
}

void ft_exec_systemcmd(t_command** cmd)
{
    //printf("System Command Exec\n");
    char *path = "/bin";
    char **dirs;
    int i = 0;

    

    dirs = ft_split(path, ':');
    
    
    path = ft_strjoin(path, "/");
    path = ft_strjoin(path, (*cmd)->argv[0]);

    //if ((*cmd)->argv[1])
    //    printf("arg = %s\n", (*cmd)->argv[1]);

    //printf("path= %s\n", path);
    
    if (execve(path, (*cmd)->argv, (*cmd)->envp) == -1)
    {
        printf("Comando non trovato\n");
    }
  
    
}

void ft_execute(t_command **cmd, t_env_vars **env_list)
{
    pid_t childPid;

    childPid = fork();
    printf("env list = %s\n", (*env_list)->env_str);
    //printf("parola chiave= %s\n", (*cmd)->argv[0]);
    if (childPid < 0)
        perror("Fork() error");
    else if (childPid == 0) //Child Process
    {
        //printf("parola chiave child= %s\n", (*cmd)->argv[0]);
        if ((*cmd)->is_builtin)
            ft_exec_builtin(cmd, env_list);
        else
            ft_exec_systemcmd(cmd);
    }
    else //Parent Process 
    {
        wait(&childPid);
    }
}