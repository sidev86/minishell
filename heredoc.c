/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:28:29 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:28:31 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_end_token(char *input_line, t_command **cmd,
		int *end_token_index)
{
	int	last_end_token_index;

	last_end_token_index = (*cmd)->heredoc_counter - 1;
	if (ft_strcmp(input_line, (*cmd)->end_tokens[*end_token_index]) == 0)
	{
		if (*end_token_index == last_end_token_index)
		{
			free(input_line);
			return (1);
		}
		else
			(*end_token_index)++;
	}
	return (0);
}

static void	process_heredoc_line(t_command **cmd, char *input_line,
		int *line_count)
{
	int		i;
	int		j;
	char	*output;
	t_env_vars **env_list;
	
	env_list = 0;
	output = (char *)malloc(ft_strlen(input_line) * 100);
	i = 0;
	j = 0;
	while (input_line[i])
	{
		if (input_line[i] == '$' && is_alphanumeric(input_line[i + 1]))
		{
			i++;
			extract_and_handle(output, &j, input_line, &i, env_list);
		}
		else
			output[j++] = input_line[i++];
	}
	output[j] = '\0';
	(*line_count)++;
	(*cmd)->heredoc_text = (char **)ft_realloc((*cmd)->heredoc_text,
			(*line_count) * sizeof(char *));
	(*cmd)->heredoc_text[(*line_count) - 1] = ft_strdup(output);
	free(output);
}

static void	handle_input_condition(t_command **cmd, char *input_line,
		int *end_token_index, int *line_count)
{
	int	last_end_token_index;

	last_end_token_index = (*cmd)->heredoc_counter - 1;
	if (last_end_token_index == 0)
		process_heredoc_line(cmd, input_line, line_count);
	else if (last_end_token_index > 0
		&& *end_token_index == last_end_token_index)
	{
		if (!(*cmd)->skip_terminator)
			(*cmd)->skip_terminator = 1;
		else
			process_heredoc_line(cmd, input_line, line_count);
	}
}

void	ft_heredoc(t_command **cmd)
{
	char	*input_line;
	int		end_token_index;
	int		line_count;

	end_token_index = 0;
	(*cmd)->skip_terminator = 0;
	line_count = 0;
	while (1)
	{
		input_line = readline("> ");
		if (handle_end_token(input_line, cmd, &end_token_index))
		{
			(*cmd)->lines_heredoc = line_count;
			break ;
		}
		handle_input_condition(cmd, input_line, &end_token_index, &line_count);
		free(input_line);
	}
}

void	ft_check_if_heredoc(t_command **cmd)
{
	int	j;

	j = 0;
	if (ft_strcmp((*cmd)->argv[0], "cat") == 0 && (*cmd)->has_heredoc)
	{
		while (j < (*cmd)->lines_heredoc)
		{
			printf("%s\n", (*cmd)->heredoc_text[j]);
			j++;
		}
		exit(0);
	}
}
