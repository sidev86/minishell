#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "minishell.h"


int ft_count_tokens(char* input)
{
    int i = 0;
    int tokens;
    char q;
    tokens = 0;

    while(input[i] && (input[i] == ' ' || input[i] == '\t'))
        i++;
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            q = input[i];
            i++;
            while(input[i] != '\0' && input[i] != q)
                i++;
            tokens++;
            i++;
        }
        else if (input[i] != ' ' && input[i] != '\t')
        {
            while(input[i] && input[i] != ' ' && input[i] != '\t' && input[i] != '\'' && input[i] != '"')
                i++;
            tokens++;
        }
        else
            i++;
    }
    return (tokens);
}


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


char* ft_get_first_token(char* input)
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
}

int ft_check_missing_quotes(char* input)
{
    int i = 0;
    int j = 0; 
    char q; 

    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            q = input[i];
            j = i + 1;
            while(input[j] != q && input[j] != '\0')
                j++;
            if (input[j] == q)
                i = j + 1;
            else if (input[j] == '\0' || input[j] != q)
                return(1);
        }
        else
            i++;   
    }
    return(0);
}

int ft_get_token_length(char* input, int i, char q)
{
    int len = 0;
    while (input[i] && input[i] != q)
        len++;
    return (len);
}

char* ft_get_quoted_token(char* input, int i)
{
    char *token; 
    char q;
    int len; 
    q = input[i];
    i++;
    
    len = ft_get_token_length(input, i, q);
    token = (char*)malloc(sizeof(char) * (len + 1));
    while (input[i] && input[i] != q)
    {
        token[i] = input[i];
        i++;
    }
    token[i] = '\0';
    return (token);
}

int ft_next_token_index(char* input, int i)
{
    char q;
    
    q = input[i];
    i++;
    while (input[i] && input[i] != q)
        i++;
    if (input[i] == q)
        i++;
    return (i);
}



void ft_parsing(char* input)
{
    char** cmd_line;
    int i; 
    int token_num;

    token_num = 0; 
    i = 0;
    if (ft_check_missing_quotes(input))
    {
        printf("Error. Missing quotes\n");
        return;
    }
    token_num = ft_count_tokens(input);
    printf("Numero di tokens = %d\n", token_num);
    
    cmd_line = (char**)malloc(sizeof(char*) * (token_num + 1));

    /*while (input[i])
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            cmd_line[token_num] = ft_get_quoted_token(input, i);
            i = ft_next_token_index(input, i);
        }
    }*/



    //prendo prima parola (comando)
    //cmd_line[0] = ft_get_first_token(input);

    //cmd_line = ft_split(input, ' ');
    

    //printf("Il numero di tokens del comando è: %d\n", ft_count_tokens(cmd_line));

    //execute_command(cmd_line);

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
        ft_parsing(input);
        add_history(input);
        
    }
    return 0;
}
