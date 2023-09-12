#include "minishell.h"

void ft_create_env_list(t_env_vars **first, char **envp)
{
    int i; 

    i = 0; 
    t_env_vars *curr;
    
    if (i == 0 && envp[i])
        *first = malloc(sizeof(t_env_vars));
    curr = *first; 
    while (envp[i])
    {
        curr->env_str = envp[i];
        curr->var = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
        //printf("corrente variabile = %s\n", curr->var);
        if (envp[i + 1])
        {
            curr->next = malloc(sizeof(t_env_vars));
            curr = curr->next;
        }
        else 
            curr->next = NULL; 
        i++; 
    }
}

void ft_print_env_list(t_env_vars **first)
{
    t_env_vars *curr; 

    curr = *first; 
    
    while (curr != NULL)
    {
        printf("%s\n", curr->env_str);
        curr = curr->next; 
    }
}

int ft_env_var_exists(t_env_vars **env_list, char *var)
{
    t_env_vars *curr;
    curr = *env_list;
    //printf("curent var = %s\n", curr->var);
    while (curr)
    {
        if (!strcmp(curr->var, var))
            return 1;
        curr = curr->next;
    }
    return 0;
}