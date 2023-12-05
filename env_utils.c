#include "minishell.h"

void ft_create_env_list(t_env_vars **first, char **envp)
{
    int i; 
    t_env_vars *curr;
    
    i = 0; 
    if (i == 0 && envp[i])
        *first = malloc(sizeof(t_env_vars));
    curr = *first; 
    while (envp[i])
    {
        curr->env_str = envp[i];
        curr->var = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
        curr->value = ft_substr(envp[i], ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '=')) + 1, envp[i] - ft_strchr(envp[i], '='));
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

int ft_env_var_exists(t_env_vars ***env_list, char *var)
{
    t_env_vars *curr;
    curr = **env_list;
    //printf("curent var = %s\n", curr->var);
    while (curr)
    {
        if (!ft_strcmp(curr->var, var))
            return 1;
        curr = curr->next;
    }
    return 0;
}

void ft_set_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
    t_env_vars *curr;
    
    curr = **env_list;
    while(curr->next)
            curr = curr->next; 
    curr->next = malloc(sizeof(t_env_vars));
    curr = curr->next; 
    curr->env_str = env_str;
    
    
    curr->var = ft_substr(env_str, 0, var_len);
    curr->value = ft_substr(env_str, var_len + 1, ft_strlen(env_str) - var_len - 1);
    curr->next = NULL;
}

void ft_update_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
    t_env_vars *curr;
    curr = **env_list;
    while(ft_strcmp(curr->var, ft_substr(env_str, 0, var_len)))
            curr = curr->next; 
    curr->env_str = env_str;
    
    curr->var = ft_substr(env_str, 0, var_len);
    curr->value = ft_substr(env_str, var_len + 1, ft_strlen(env_str) - var_len - 1);
   
}

void ft_remove_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
    t_env_vars *curr;
    int num_element;
    
    curr = **env_list;
    num_element = 1;
    while(ft_strcmp(curr->var, ft_substr(env_str, 0, var_len)))
    {
        curr = curr->next;
        num_element++;
    }
    curr->env_str = NULL;
    curr->var = NULL;
    curr->value = NULL;
    if (curr->next && num_element == 1)
    {
    	**env_list = curr->next;
    	free(curr);
    }
    else if (curr->next && num_element > 1)
    {
        curr = **env_list;
        while(curr->next->env_str)
            curr = curr->next;
        free(curr->next);
        curr->next = curr->next->next;
    }
    else
    {
        curr = **env_list;
        while (curr->next->env_str)
            curr = curr->next;
        curr->next = NULL;   
    }     
}
