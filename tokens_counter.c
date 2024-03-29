/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <sibrahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:25 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/26 11:32:24 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_token_in_quotes(char *input, int i, int *tokens)
{
	char	c;

	c = input[i++];
	while (input[i] != c && input[i])
		i++;
	i++;
	if (ft_is_space(input[i]) || ft_is_redir_pipe(input[i]) || !input[i])
		(*tokens)++;
	return (i);
}

static int	ft_token_no_quotes(char *input, int i, int *tokens)
{
	while (ft_is_space(input[i]))
		i++;
	while (!ft_is_quote(input[i]) && !ft_is_space(input[i])
		&& !ft_is_redir_pipe(input[i]) && input[i])
		i++;
	if (ft_is_space(input[i]) || ft_is_redir_pipe(input[i]) || !input[i]
		|| !input[i + 1])
		(*tokens)++;
	return (i);
}

static int	ft_check_after_redir(char *input, int i)
{
	int	letters;

	letters = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '|')
			letters = 1;
		if (input[i] == '|')
		{
			if (!letters)
				break ;
		}
		i++;
	}
	if (!letters)
	{
		errors_manager(SET_CODE, 2, NULL, NULL);
		errors_manager(PRINT, 1, "syntax error near unexpected token (>,<)\n",
			"Error");
		return (1);
	}
	return (0);
}

static int	ft_redir_pipe_token(char *input, int i, int *tokens)
{
	(*tokens)++;
	if (input[i] == '|')
		i++;
	else if (input[i] == '>' || input[i] == '<')
	{
		i++;
		if (input[i - 1] == '>' && input[i] == '>')
			i++;
		else if (input[i - 1] == '<' && input[i] == '<')
			i++;
		else if ((input[i - 1] == '>' && input[i] == '<') || (input[i
					- 1] == '<' && input[i] == '>') || ft_strlen(input) == 1)
		{
			errors_manager(SET_CODE, 2, NULL, NULL);
			errors_manager(PRINT, 1,
				"syntax error near unexpected token (>,<)\n", "Error");
			return (0);
		}
		if (ft_check_after_redir(input, i))
			return (0);
	}
	return (i);
}

int	ft_count_tokens(char *input)
{
	int	i;
	int	tokens;

	i = 0;
	tokens = 0;
	while (input[i])
	{
		while (ft_is_space(input[i]) && input[i])
			i++;
		if (ft_is_quote(input[i]) && input[i])
			i = ft_token_in_quotes(input, i, &tokens);
		else if (!ft_is_quote(input[i]) && !ft_is_redir_pipe(input[i])
			&& input[i])
			i = ft_token_no_quotes(input, i, &tokens);
		if (ft_is_redir_pipe(input[i]))
			i = ft_redir_pipe_token(input, i, &tokens);
		if (i == 0)
			return (0);
	}
	return (tokens);
}
