/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:30:39 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:30:41 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_token_in_quotes(char *input, int i, int *tokens)
{
	char	c;

	c = input[i++];
	while (input[i] != c && input[i])
		i++;
	if (ft_is_space(input[i + 1]) || \
	ft_is_redir_pipe(input[i + 1]) || !input[i + 1])
		(*tokens)++;
	return (i);
}

static int	ft_token_no_quotes(char *input, int i, int *tokens)
{
	char	c;

	while (ft_is_space(input[i]))
		i++;
	while (!ft_is_quote(input[i]) && !ft_is_space(input[i])
		&& !ft_is_redir_pipe(input[i]) && input[i])
		i++;
	if (ft_is_quote(input[i]))
	{
		c = input[i++];
		while (input[i] != c && input[i])
			i++;
		i++;
	}
	if (ft_is_space(input[i]) || ft_is_redir_pipe(input[i]) || !input[i]
		|| !input[i + 1])
		(*tokens)++;
	return (i);
}

static int	ft_redir_pipe_token(char *input, int i, int *tokens)
{
	(*tokens)++;
	if (input[i] == '|')
		i++;
	else if (input[i] == '>' || input[i] == '<')
	{
		i++;
		if (input[i + 1] == '>' || input[i + 1] == '<')
			i++;
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
		if (ft_is_quote(input[i]))
			i = ft_token_in_quotes(input, i, &tokens);
		else if (!ft_is_quote(input[i]) && !ft_is_redir_pipe(input[i])
			&& input[i])
			i = ft_token_no_quotes(input, i, &tokens);
		if (ft_is_redir_pipe(input[i]))
			i = ft_redir_pipe_token(input, i, &tokens);
		if (input[i])
			i++;
	}
	return (tokens);
}
