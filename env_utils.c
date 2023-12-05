#include "minishell.h"


int ft_count_environment_vars(char **envp)
{
    int i = 0;
    while (envp[i])
        i++;
    return (i);
}

char **ft_get_environment_vars(char **envp)
{
    char **env;
    int i = 0;
    env = (char**)malloc(sizeof(char*) * ft_count_environment_vars(envp) + 1);
    while (envp[i])
    {
        env[i] = ft_strjoin(envp[i], "\0");
        i++;
    }
    env[i] = NULL;
    return (env);
}


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

