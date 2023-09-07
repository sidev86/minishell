#include "minishell.h"

void ft_echo(t_command **cmd)
{
    int i = 1;
    while (i < (*cmd)->argc)
    {
        printf("%s ", (*cmd)->argv[i]);
        i++;
    }
    printf("\n");
}

void ft_cd(t_command **cmd)
{
    printf("cd\n");
}

void ft_pwd(t_command **cmd)
{
    printf("pwd\n");
}

void ft_export(t_command **cmd)
{
    printf("export\n");
}

void ft_unset(t_command **cmd)
{
    printf("unset\n");
}

void ft_env(t_command **cmd)
{
    printf("env\n");
}

void ft_exit(t_command **cmd)
{
    printf("exit\n");
}