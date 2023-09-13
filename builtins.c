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

void ft_export(t_command **cmd, t_env_vars **env_list)
{
    char *env_arg;
    int var_len;
    t_env_vars *curr; 
    env_arg = (*cmd)->argv[1];
    curr = *env_list;
    var_len = (ft_strlen(env_arg) - ft_strlen(ft_strchr(env_arg,'=')));
    if(!ft_env_var_exists(env_list, ft_substr(env_arg, 0, var_len)) && env_arg != NULL)
            ft_set_env_var(env_list, env_arg, var_len);
    else if (ft_env_var_exists(env_list, ft_substr(env_arg, 0, var_len)) && env_arg != NULL)
            ft_update_env_var(env_list, env_arg, var_len);
    
    /*if(env_arg)
    {
        while(curr->next)
            curr = curr->next; 
        curr->next = malloc(sizeof(t_env_vars));
        curr = curr->next; 
        curr->env_str = env_arg;
        
        //printf("var len = %d\n", var_len);
        
        curr->var = ft_substr(env_arg, 0, var_len);
        //curr->var = ft_strjoin(curr->var, "\0");
        printf("curr var = %s\n", curr->var); 
        curr->next = NULL;
    }   */
}

void ft_unset(t_command **cmd)
{
    printf("unset\n");
}

void ft_env(t_command **cmd, t_env_vars **env_list)
{
    t_env_vars *curr; 

    curr = *env_list; 
    while (curr != NULL)
    {
        printf("%s\n", curr->env_str);
        curr = curr->next; 
    }
}

void ft_exit(t_command **cmd)
{
    printf("exit\n");
}