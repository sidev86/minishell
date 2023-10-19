#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "minishell.h"

char* ft_wait_for_input()
{
    char* input;
    input = readline("minishell$ ");
    if (input[0] == '\0')
        return NULL;
    return (input);
}

int ft_command_is_exit(char *input)
{
    int cmd_len; 
    int i; 
    cmd_len = 0;
    i = 0; 
    while (input[i] != ' ' && input[i] != '\t' && input[i])
    {
        cmd_len++;
        i++; 
    }

    //printf("cmd len = %d\n", cmd_len);
    if (cmd_len == 4 && !strcmp(ft_substr(input, 0, cmd_len), "exit"))    
        return(1);
    return(0);        
}

int main(int argc, char **argv, char **envp) 
{
    char* input;
    char* cmd_key;
    t_env_vars *first_env;
    int i = 0;
    first_env = 0;
    ft_create_env_list(&first_env, envp);
    setenv("TERM", "xterm", 1); // Imposta la variabile TERM a un valore valido

    //ft_print_env_list(&first_env); 
    while (1)
    {
        input = ft_wait_for_input();
        if (input != NULL)
        {
            if (ft_command_is_exit(input))
                return 1; 
        
                ft_lex(input, &first_env, envp);
                add_history(input);
            //if (cmd_line[0] && (strcmp(cmd_line, "exit") == 0))
            //    break; 
        }    
    }
    return 0;
}





//FUNCTIONS THAT I DON'T USE ANymore

/*char* ft_get_first_token(char* input)
{
    char* token;
    int i = 0;
    while (input[i] == ' ' || input[i] == '\t')
        i++;
    while (input[i] && input[i] != ' ' && input[i] != '\t')
    {
        token[i] = input[i];
        i++;     
    }      
    return (token);    
}*/

/*char* ft_get_quoted_token(char* input, int i)
{
    char *token; 
    char q;
    int len; 
    q = input[i];
    i++;
    
    //len = ft_get_token_length(input, i, q);
    token = (char*)malloc(sizeof(char) * (len + 1));
    while (input[i] && input[i] != q)
    {
        token[i] = input[i];
        i++;
    }
    token[i] = '\0';
    return (token);
}*/