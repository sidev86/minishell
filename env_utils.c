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

int ft_env_var_exists(t_env_vars ***env_list, char *var)
{
    t_env_vars *curr;
    curr = **env_list;
    //printf("curent var = %s\n", curr->var);
    while (curr)
    {
        if (!strcmp(curr->var, var))
            return 1;
        curr = curr->next;
    }
    return 0;
}

void ft_set_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
    t_env_vars *curr;
    curr = **env_list;
    printf("set env curr str = %s\n", curr->env_str);
    while(curr->next)
            curr = curr->next; 
    curr->next = malloc(sizeof(t_env_vars));
    if (curr->next)
        printf("allocation success\n");
    curr = curr->next; 
    curr->env_str = env_str;
    
    //printf("var len = %d\n", var_len);
    
    curr->var = ft_substr(env_str, 0, var_len);
    curr->value = ft_substr(env_str, var_len + 1, ft_strlen(env_str) - var_len - 1);
    //curr->var = ft_strjoin(curr->var, "\0");
    //printf("curr var = %s\n", curr->var); 
    //printf("curr value = %s\n", curr->value);
    curr->next = NULL;
}

void ft_update_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
    t_env_vars *curr;
    curr = **env_list;
    while(strcmp(curr->var, ft_substr(env_str, 0, var_len)))
            curr = curr->next; 
    curr->env_str = env_str;
    //printf("stringa corrente in lista= %s\n", curr->env_str);
    //printf("var len = %d\n", var_len);
    
    curr->var = ft_substr(env_str, 0, var_len);
    curr->value = ft_substr(env_str, var_len + 1, ft_strlen(env_str) - var_len - 1);
    //curr->var = ft_strjoin(curr->var, "\0");
    //printf("curr var = %s\n", curr->var); 
    //printf("curr value = %s\n", curr->value);
}

void ft_remove_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
    t_env_vars *curr;
    curr = **env_list;
    //printf("rimuovo env var\n");
    while(strcmp(curr->var, ft_substr(env_str, 0, var_len)))
        curr = curr->next;

    //printf("curr var = %s\n", curr->var);
    curr->env_str = NULL;
    curr->var = NULL;
    curr->value = NULL;
    if (curr->next != NULL)
    {
        //printf("elemento in mezzo\n");
        curr = **env_list;
        while(curr->next->env_str)
            curr = curr->next;
        //printf("env corrente = %s\n", curr->env_str);
        //printf("env next next = %s\n", curr->next->next->env_str);
        curr->next = curr->next->next;
    }
    else
    {
        //printf("ultimo elemento\n");
        curr = **env_list;
        while (curr->next->env_str)
            curr = curr->next;
        //printf("env corrente = %s\n", curr->env_str);
        curr->next = NULL;   
    }
        
}