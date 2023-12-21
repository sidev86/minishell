/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:29:43 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:29:44 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_variable(char *output, int *j, char *variabile, t_env_vars **env_list)
{
	char	*valorevariabile;
	
	output[*j] = '\0';
	//printf("variabile = %s\n", variabile);
	valorevariabile = ft_get_env_var_value(env_list, variabile);
	//printf("valore variabile = %s\n", valorevariabile);
	//printf("len val variabile = %ld\n", ft_strlen(valorevariabile));
	if (valorevariabile)
	{
		ft_strcat(output, valorevariabile);
		(*j) += ft_strlen(valorevariabile);
	}
	else
		handle_exit_code(output, j, variabile);
}

void	extract_and_handle(char *output, int *j, char *input, int *i, t_env_vars **env_list)
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
	handle_variable(output, j, variabile, env_list);
	free(variabile);
}

static void	handle_quoted_input(char *output, int *j, char *input, int *i, t_env_vars **env_list)
{
	(*i)++;
	while (input[*i] != '"')
	{
		if (input[*i] == '$' && is_alphanumeric(input[*i + 1]))
		{
			(*i)++;
			extract_and_handle(output, j, input, i, env_list);
		}
		else
		{
			output[(*j)++] = input[(*i)++];
		}
	}
	(*i)++;
}

static void	handle_input(char *output, int *j, char *input, int *i, t_env_vars **env_list)
{
	if (input[*i] == '"')
		handle_quoted_input(output, j, input, i, env_list);
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
		output[(*j)] = '\0';
		extract_and_handle(output, j, input, i, env_list);
	}
	else
	{
		output[(*j)++] = input[(*i)++];
	}
}

char	*handle_quotes(char *input, t_env_vars **env_list)
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
		handle_input(output, &j, input, &i, env_list);
	}
	output[j] = '\0';
	return (output);
}
