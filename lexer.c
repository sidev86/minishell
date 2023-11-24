#include "minishell.h"

int ft_is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int ft_is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int ft_is_redir_pipe(char c)
{
	return (c == '|' || c == '>' || c == '<');
}


int ft_count_tokens(char* input)
{
	int		i;
	int		tokens;
	char	c;

	i = 0;
	tokens = 0;
	while (input[i])
	{
		while (ft_is_space(input[i]) && input[i])
			i++;
		if (ft_is_quote(input[i]))
		{
			c = input[i++];
			while (input[i] != c && input[i])
				i++;
			// Conta le virgolette solo se sono strettamente accoppiate
			if (input[i] == c)
			{
				tokens++;
				i++;
			}
			else
			{
		        // Manca la chiusura delle virgolette, considera il resto della stringa come un token
				tokens++;
				//break;
			}
		}
		else if (!ft_is_quote(input[i]) && !ft_is_redir_pipe(input[i]) && input[i])
		{
			// Se non è una virgoletta e non è un carattere di redirezione/pipe
			// allora è il primo carattere di un nuovo token
			tokens++;
			// Leggi fino alla fine del token
			while (!ft_is_quote(input[i]) && !ft_is_space(input[i]) && !ft_is_redir_pipe(input[i]) && input[i])
				i++;
			// Se alla fine del token ci sono virgolette, contale come parte del token
			while (ft_is_quote(input[i]))
			{
				c = input[i++];
				while (input[i] != c && input[i])
					i++;
				// Conta le virgolette solo se sono strettamente accoppiate
				if (input[i] == c)
				{
					tokens++;
					i++;
				}
				else
				{
				// Manca la chiusura delle virgolette, considera il resto della stringa come un token
					tokens++;
					//break;
				}
			}
		}
		if (ft_is_redir_pipe(input[i]))
		{
			tokens++;
			// Se è '>', verifica se c'è un altro '>' immediatamente dopo
			if (input[i] == '>' && input[i + 1] == '>')
		        	i++;
		}
		// Aggiunto il controllo per evitare l'accesso oltre la fine della stringa
		if (input[i])
			i++;
	}
	return tokens;
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

    while (input[i])
    {
        // Ignora spazi iniziali
        while (input[i] && (input[i] == ' ' || input[i] == '\t'))
            i++;

        if (input[i] == '|' || input[i] == '>' || input[i] == '<')
        {
            // Carattere di redirezione/pipe
            len = 1;
            return len;
        }
        else if (input[i] == '\'' || input[i] == '"')
        {
            // Inizio di una virgoletta
            len = ft_get_quotedtoken_len(input, i, input[i]);
            i += len - 1;  // Sottrai 1 perché il loop incrementa di nuovo i
            return len;
        }
        else
        {
            // Carattere non speciale
            len++;
            i++;

            // Leggi fino alla fine del token
            while (input[i] && !ft_is_space(input[i]) && !ft_is_redir_pipe(input[i]) && input[i] != '\'' && input[i] != '"')
            {
                len++;
                i++;
            }

            return len;
        }
    }

    return len;
}

/*int ft_cmd_in_path(char* cmd)
{
    char *path;

    path = getenv("PATH");

    printf("path = %s\n", path);
    return 1;
}*/

int ft_get_redirpipe_len(char *input, int i)
{
	if (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
			return (2);
		else if (input[i] == '<' && input[i + 1] == '<')
			return (2);
	}
	return (1);
}


void ft_lex(char* input, t_env_vars **env_list, char **envp)
{
	t_tokens	*cmd_line; 
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
	printf("Numero di tokens = %d\n", tokens_total);
	cmd_line = malloc(sizeof(t_tokens) * (tokens_total));
	if (!cmd_line)
		printf("Malloc error\n");
	i = 0;
	//salvo e stampo i token
	while (token_num < tokens_total && input[i])
	{
		//skippo eventuali spazi iniziali
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		    i++;
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			token_len = ft_get_redirpipe_len(input, i);
		else
			token_len = ft_get_token_len(input, i);
		cmd_line[token_num].token = ft_substr(input, i, token_len);
		//printf("stringa prima = %s\n", cmd_line[token_num].token);
		printf("Token %d: \"%s\" - Lunghezza: %d\n", token_num + 1, cmd_line[token_num].token, token_len);
		cmd_line[token_num].token = handle_quotes(cmd_line[token_num].token);
		//printf("stringa dopo = %s\n", cmd_line[token_num].token);
		i += token_len;
		token_num++;
	}
	if (strcmp(cmd_line[0].token, "exit") != 0)
        	ft_parse(cmd_line, tokens_total, env_list, envp);
        free(cmd_line);
}
