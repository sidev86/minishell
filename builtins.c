#include "minishell.h"

void ft_echo(char** cmd)
{
    int i = 1;
    while (cmd[i])
    {
        printf("%s ", cmd[i]);
        i++;
    }
    printf("\n");
}

void ft_cd()
{
    printf("cd\n");
}

void ft_pwd()
{
    printf("pwd\n");
}

void ft_export()
{
    printf("export\n");
}

void ft_unset()
{
    printf("unset\n");
}

void ft_env()
{
    printf("env\n");
}

void ft_exit()
{
    printf("exit\n");
}