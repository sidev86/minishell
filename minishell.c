#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "minishell.h"

char* ft_wait_for_input()
{
    char* input;
    input = readline("minishell$ ");
    
    return (input);
}

int main(int argc, char **argv, char **envp) 
{
    char* input;
    t_env_vars *first_env;
    int i = 0;
    first_env = 0; 

    ft_create_env_list(&first_env, envp);
    //ft_print_env_list(&first_env); 
    while (1)
    {
        input = ft_wait_for_input();
        if (input)
        {
            ft_lex(input, &first_env);
            add_history(input);
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