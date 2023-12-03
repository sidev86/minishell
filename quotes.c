#include "minishell.h"

extern int e_code; 

int	is_alphanumeric(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '?');
}

void	handle_variable(char *output, int *j, char *variabile)
{
	char	*valorevariabile;
	int	i;
	
	i = 0;
	valorevariabile = getenv(variabile);
	//printf("valore variabile = %s\n", valorevariabile);
	//printf("strlen = %ld\n", strlen(valorevariabile));
	if (valorevariabile)
	{
		ft_strcat(output, valorevariabile);
		(*j) += ft_strlen(valorevariabile);
	}
	else 
	{
		//printf("valore variabile = %s\n", variabile);
		if (variabile[i] == '?')
		{
			ft_strcat(output, ft_itoa(e_code));
			(*j) += ft_strlen(ft_itoa(e_code));
			if (variabile[i + 1] != ' ' && variabile[i + 1])
			{
				while(variabile[i + 1] != ' ' && variabile[i + 1])
					output[(*j)++] = variabile[++i];
			}
			//(*j) += strlen(variabile);
		}
	}
}

void	extract_and_handle(char *output, int *j, char *input, int *i)
{
	int		k;
	char	*variabile;

	variabile = (char *)malloc(ft_strlen(input) * 100);
	if (!variabile)
	{
		perror("Memory allocation error");
		exit(1);
	}
	k = 0;
	while (is_alphanumeric(input[*i]))
	{
		variabile[k++] = input[(*i)++];
	}
	variabile[k] = '\0';
	handle_variable(output, j, variabile);
	//free(variabile);
}

void handle_input(char *output, int *j, char *input, int *i)
{
	if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] != '"')
		{
			//if (input[*i] == '\\')
			//	(*i)++;
			if (input[*i] == '$' && is_alphanumeric(input[*i+1]))
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
	else if (input[*i] == '$' && is_alphanumeric(input[*i+1]))
	{
		(*i)++;
		extract_and_handle(output, j, input, i);
	}
	else
	{
			output[(*j)++] = input[(*i)++];	
	}
}

char	*handle_quotes(char *input)
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
    output = (char *)malloc(ft_strlen(input) * 100);
    if (!output)
    {
        perror("Memory allocation error");
        exit(1);
    }
    while (input[i])
    {
        handle_input(output, &j, input, &i);
    }
    output[j] = '\0';
    return (output);
}
