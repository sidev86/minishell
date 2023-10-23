#include "minishell.h"

int	is_alphanumeric(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

void	handle_variable(char *output, int *j, char *variabile)
{
	char	*valorevariabile;

	valorevariabile = getenv(variabile);
	if (valorevariabile)
	{
		strcat(output, valorevariabile);
		(*j) += strlen(valorevariabile);
	}
}

void	extract_and_handle(char *output, int *j, char *input, int *i)
{
	int		k;
	char	*variabile;

	variabile = (char *)malloc(strlen(input) + 1);
	if (!variabile)
	{
		perror("Errore di allocazione di memoria");
		exit(1);
	}
	k = 0;
	while (is_alphanumeric(input[*i]))
	{
		variabile[k++] = input[(*i)++];
	}
	variabile[k] = '\0';
	handle_variable(output, j, variabile);
	free(variabile);
}

void handle_input(char *output, int *j, char *input, int *i)
{
	if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] != '"')
		{
			if (input[*i] == '\\')
				(*i)++;
			else if (input[*i] == '$')
			{
				(*i)++;
				extract_and_handle(output, j, input, i);
			}
			else
				output[(*j)++] = input[(*i)++];
		}
		(*i)++;
	}
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] != '\'')
			output[(*j)++] = input[(*i)++];
		(*i)++;
	}
	else if (input[*i] == '$')
	{
		(*i)++;
		extract_and_handle(output, j, input, i);
	}
	else
	{
		if (input[*i] == '\\')
			(*i)++;
		else
			output[(*j)++] = input[(*i)++];	
	}
}

char	*manipolaVirgolette(char *input)
{
    int		i;
    int		j;
    //int		ft_doppie;
    //int		ft_singole;
    char	*output;

    i = 0;
    j = 0;
    //ft_doppie = 0;
    //ft_singole = 0;
    output = (char *)malloc(strlen(input) + 1);
    if (!output)
    {
        perror("Errore di allocazione di memoria");
        exit(1);
    }
    while (input[i])
    {
        handle_input(output, &j, input, &i);
    }
    output[j] = '\0';
    return (output);
}
