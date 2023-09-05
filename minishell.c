#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "minishell.h"

void execute_command(char **cmd)
{
    if (!strcmp(cmd[0], "echo"))
        ft_echo(cmd);
    else if (!strcmp(cmd[0], "cd"))
        ft_cd(cmd);
    else if (!strcmp(cmd[0], "pwd"))
        ft_pwd();
    else if (!strcmp(cmd[0], "export"))
        ft_export();
    else if (!strcmp(cmd[0], "unset"))
        ft_unset();
    else if (!strcmp(cmd[0], "env"))
        ft_env();
    else if (!strcmp(cmd[0], "exit"))
        ft_exit();
    else
        printf("Error. Command not found\n");
}

char* ft_wait_for_input()
{
    char* input;
    input = readline("minishell$ ");
    
    return (input);
}

int main() 
{
    char* input;

    while (1)
    {
        input = ft_wait_for_input();
        ft_lexer(input);
        add_history(input); 
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