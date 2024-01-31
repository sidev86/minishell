/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:41:10 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:41:11 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_quotedtoken_len(char *input, int i, char q)
{
	int	len;

	len = 0;
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

static int	ft_next_token_index(char *input, int i)
{
	char	q;

	q = input[i];
	i++;
	while (input[i] && input[i] != q)
		i++;
	if (input[i] == q)
		i++;
	return (i);
}

int	ft_get_token_len(char *input, int i)
{
	int	len;

	len = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\\'
			&& input[i] != ';' && !ft_is_redir_pipe(input[i]))
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
			return (len);
	}
	return (len);
}
