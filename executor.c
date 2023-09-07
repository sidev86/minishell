#include "minishell.h"


void ft_exec_builtin(t_command** cmd)
{
    //printf("comando da eseguire= %s\n", (*cmd)->argv[0]);
    if (!strcmp((*cmd)->argv[0], "echo"))
        ft_echo(cmd);
    else if (!strcmp((*cmd)->argv[0], "cd"))
        ft_cd(cmd);
    else if (!strcmp((*cmd)->argv[0], "pwd"))
        ft_pwd(cmd);
    else if (!strcmp((*cmd)->argv[0], "export"))
        ft_export(cmd);
    else if (!strcmp((*cmd)->argv[0], "unset"))
        ft_unset(cmd);
    else if (!strcmp((*cmd)->argv[0], "env"))
        ft_env(cmd);
    else if (!strcmp((*cmd)->argv[0], "exit"))
        ft_exit(cmd);
    else
        printf("Error. Commando not found\n");
}

void ft_exec_systemcmd(t_command** cmd)
{
    printf("System Command Exec\n");
}

void ft_execute(t_command **cmd)
{
    pid_t childPid;

    childPid = fork();
    //printf("parola chiave= %s\n", (*cmd)->argv[0]);
    if (childPid < 0)
        perror("Fork() error");
    else if (childPid == 0) //Child Process
    {
        //printf("parola chiave child= %s\n", (*cmd)->argv[0]);
        if ((*cmd)->is_builtin)
            ft_exec_builtin(cmd);
        else
            ft_exec_systemcmd(cmd);
    }
    else //Parent Process 
    {
        wait(&childPid);
    }
}