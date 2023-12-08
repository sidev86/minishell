#include "minishell.h"

static void	handle_variable(char *output, int *j, char *variabile)
{
	char	*valorevariabile;
	int		i;
	int		e_code;

	i = 0;
	valorevariabile = getenv(variabile);
	if (valorevariabile)
	{
		ft_strcat(output, valorevariabile);
		(*j) += ft_strlen(valorevariabile);
	}
	else
	{
		if (variabile[i] == '?')
		{
			e_code = errors_manager(GET_CODE, 0, NULL, NULL);
			ft_strcpy(output, ft_itoa(e_code));
			(*j) += ft_strlen(ft_itoa(e_code));
			if (variabile[i + 1] != ' ' && variabile[i + 1])
			{
				while (variabile[i + 1] != ' ' && variabile[i + 1])
					output[(*j)++] = variabile[++i];
			}
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
	free(variabile);
}

static void	handle_quoted_input(char *output, int *j, char *input, int *i)
{
	(*i)++;
	while (input[*i] != '"')
	{
		if (input[*i] == '$' && is_alphanumeric(input[*i + 1]))
		{
			(*i)++;
			extract_and_handle(output, j, input, i);
		}
		else
		{
			output[(*j)++] = input[(*i)++];
		}
	}
	(*i)++;
}

static void	handle_input(char *output, int *j, char *input, int *i)
{
	if (input[*i] == '"')
		handle_quoted_input(output, j, input, i);
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] != '\'')
		{
			output[(*j)++] = input[(*i)++];
		}
		(*i)++;
	}
	else if (input[*i] == '$' && is_alphanumeric(input[*i + 1]))
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
	char	*output;

	i = 0;
	j = 0;
	output = (char *)malloc(ft_strlen(input) * 100);
	if (!output)
	{
		perror("Memory allocation error");
		exit(1);
	}
	output[0] = '\0';
	while (input[i])
	{
		handle_input(output, &j, input, &i);
	}
	output[j] = '\0';
	return (output);
}
