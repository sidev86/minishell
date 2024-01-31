/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <sibrahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:41:03 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/26 11:29:45 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_missing_quotes(char *input)
{
	int		i;
	int		j;
	char	q;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			q = input[i];
			j = i + 1;
			while (input[j] != q && input[j] != '\0')
				j++;
			if (input[j] == q)
				i = j + 1;
			else if (input[j] == '\0' || input[j] != q)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

static int	ft_get_redirpipe_len(char *input, int i)
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

static void	ft_split_into_tokens(char *input, t_tokens **line, int tokens_total)
{
	int	i;
	int	token_num;
	int	token_len;

	i = 0;
	token_num = 0;
	token_len = 0;
	while (token_num < tokens_total && input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			token_len = ft_get_redirpipe_len(input, i);
		else if (input[i] == '\\' || input[i] == ';')
			token_len = 1;
		else
			token_len = ft_get_token_len(input, i);
		(*line)[token_num].token = ft_substr(input, i, token_len);
		i += token_len;
		token_num++;
	}
}

void	ft_lex(char *input, t_env_vars **env_list, char **envp)
{
	t_tokens	*cmd_line;
	int			tokens_total;

	if (ft_check_missing_quotes(input))
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Missing quotes\n", "Error");
		return ;
	}
	if (ft_wrong_pipe_token(input))
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Syntax error near unexpected token '|'\n",
			"Error");
		return ;
	}
	tokens_total = ft_count_tokens(input);
	if (tokens_total == 0)
		return ;
	cmd_line = malloc(sizeof(t_tokens) * (tokens_total));
	if (!cmd_line)
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
	ft_split_into_tokens(input, &cmd_line, tokens_total);
	ft_parse(cmd_line, tokens_total, env_list, envp);
}
