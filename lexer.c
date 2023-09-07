#include "minishell.h"


int ft_count_tokens(char* input)
{
    int i = 0;
    int tokens;
    char q;
    tokens = 0;

    while(input[i] == ' ' || input[i] == '\t')
        i++;
    while (input[i])
    {
        if (input[i] != ' ' && input[i] != '\t' && input[i + 1] != '\0')
        {
            if(input[i] == '\'' || input[i] == '"')
            {
                q = input[i];
                i++;
                //printf("q = %c\n", q);
                while(input[i] && input[i] != q)
                    i++;
                i++;
                if (!input[i])
                    tokens++;
            }
            else
                i++;
        }
        else
        {
            tokens++;
            while ((input[i] == ' ' || input[i] == '\t' || !input[i + 1]) && input[i])
                i++;
        }
    }
    return (tokens);
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

int ft_get_quotedtoken_len(char* input, int i, char q)
{
    int len = 0;
    i++;
    len++;
    while (input[i] && input[i] != q)
    {
        i++;
        len++;
    }
    if (input[i] == q)
        len++;
    return (len);
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


int ft_get_token_len(char* input, int i)
{
    int len = 0; 

    while(input[i])
    {
        if (input[i] != ' ' && input[i] != '\t')
        {
            if (input[i] == '\'' || input[i] == '"')
            {
                len += ft_get_quotedtoken_len(input, i, input[i]);
                i = ft_next_token_index(input, i);
            }
            else
            {
                len++;
                i++;     
            }    
        }
        else
            return(len);
    }
    return (len);
}



/*int ft_cmd_in_path(char* cmd)
{
    char *path;

    path = getenv("PATH");

    printf("path = %s\n", path);
    return 1;
}*/




void ft_lex(char* input)
{
    char** cmd_line;
    int i; 
    int token_num;
    int tokens_total;
    int token_len;

    token_num = 0; 
    tokens_total = 0; 
    token_len = 0; 
    
    if (ft_check_missing_quotes(input))
    {
        printf("Error. Missing quotes\n");
        return;
    }
    tokens_total = ft_count_tokens(input);
    //printf("Numero di tokens = %d\n", tokens_total);
    
    cmd_line = (char**)malloc(sizeof(char*) * (tokens_total + 1));
    if (!cmd_line)
        printf("malloc error");
    i = 0;

    //salvo e stampo i token
    while (token_num < tokens_total && input[i])
    {
        //skippo eventuali spazi iniziali
        while (input[i] && (input[i] == ' ' || input[i] == '\t'))
            i++;

        token_len = ft_get_token_len(input, i);
        cmd_line[token_num] = ft_substr(input, i, token_len);
        //printf("stringa = %s\n", cmd_line[token_num]);
        i += token_len;
        token_num++;
    }
    cmd_line[token_num] = NULL;
    ft_parse(cmd_line, tokens_total);
    
    //execute_command(cmd_line);




}

