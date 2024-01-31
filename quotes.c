/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:04 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:43:05 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_variable(int *j, char *variabile,
		t_env_vars **env_list)
{
	char	*valorevariabile;

	(*env_list)->output[*j] = '\0';
	valorevariabile = ft_get_env_var_value(env_list, variabile);
	if (valorevariabile)
	{
		ft_strcat((*env_list)->output, valorevariabile);
		(*j) += ft_strlen(valorevariabile);
	}
	else
		handle_exit_code(env_list, j, variabile);
}

void	extract_and_handle(int *j, char *input, int *i,
		t_env_vars **env_list)
{
	int		k;
	char	*variabile;

	variabile = (char *)malloc(ft_strlen(input) * 100);
	if (!variabile)
	{
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
		exit(1);
	}
	k = 0;
	while (is_alphanumeric(input[*i]))
	{
		variabile[k++] = input[(*i)++];
	}
	variabile[k] = '\0';
	handle_variable(j, variabile, env_list);
	free(variabile);
}

static void	handle_quoted_input(int *j, char *input, int *i,
		t_env_vars **env_list)
{
	(*i)++;
	while (input[*i] != '"')
	{
		if (input[*i] == '$' && is_alphanumeric(input[*i + 1]))
		{
			(*i)++;
			extract_and_handle(j, input, i, env_list);
		}
		else
			(*env_list)->output[(*j)++] = input[(*i)++];
	}
	(*i)++;
}

static void	handle_input(int *j, char *input, int *i,
		t_env_vars **env_list)
{
	if (input[*i] == '"')
		handle_quoted_input(j, input, i, env_list);
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] != '\'')
		{
			(*env_list)->output[(*j)++] = input[(*i)++];
		}
		(*i)++;
	}
	else if (input[*i] == '$' && is_alphanumeric(input[*i + 1]))
	{
		(*i)++;
		(*env_list)->output[(*j)] = '\0';
		extract_and_handle(j, input, i, env_list);
	}
	else
	{
		(*env_list)->output[(*j)++] = input[(*i)++];
	}
}

char	*handle_quotes(char *input, t_env_vars **env_list)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	(*env_list)->output = (char *)malloc(ft_strlen(input) * 100);
	if (!(*env_list)->output)
	{
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
		exit(1);
	}
	(*env_list)->output[0] = '\0';
	while (input[i])
	{
		handle_input(&j, input, &i, env_list);
	}
	(*env_list)->output[j] = '\0';
	return ((*env_list)->output);
}
