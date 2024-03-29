/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:39:34 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:39:36 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_a_valid_character(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' \
			&& c <= '9') || (c == '_'));
}

int	ft_is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	ft_is_redir_pipe(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_alphanumeric(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' \
			&& c <= '9') || c == '?');
}
