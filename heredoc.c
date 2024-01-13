/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: extrimer <extrimer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:28:29 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/28 14:25:01 by extrimer         ###   ########.fr       */
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
		int *line_count, t_env_vars **env_list)
{
	int		i;
	int		j;
	char	*output;

	output = (char *)malloc(ft_strlen(input_line) * 100);
	if (!output)
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
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
	if (!(*cmd)->heredoc_text)
		(*cmd)->heredoc_text = (char **)malloc((*line_count) * sizeof(char *));
	else
		(*cmd)->heredoc_text = (char **)ft_realloc((*cmd)->heredoc_text,((*line_count) - 1) * sizeof(char *), (*line_count) * sizeof(char *));
	if (!(*cmd)->heredoc_text)
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
	(*cmd)->heredoc_text[(*line_count) - 1] = ft_strdup(output);
	(*cmd)->lines_heredoc = (*line_count);
	free(output);
}

static void	handle_input_condition(t_command **cmd, char *input_line,
		int *end_token_index, int *line_count, t_env_vars **env_list)
{
	int	last_end_token_index;

	last_end_token_index = (*cmd)->heredoc_counter - 1;
	if (last_end_token_index == 0)
		process_heredoc_line(cmd, input_line, line_count, env_list);
	else if (last_end_token_index > 0
		&& *end_token_index == last_end_token_index) 
	{
		if (!(*cmd)->skip_terminator)
			(*cmd)->skip_terminator = 1;
		else
			process_heredoc_line(cmd, input_line, line_count, env_list);
	}
}

void	ft_heredoc(t_command **cmd, t_env_vars **env_list)
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
		handle_input_condition(cmd, input_line, &end_token_index, &line_count, env_list);
		free(input_line);
	}
}

int	ft_check_if_heredoc(t_command **cmd, char *path, char *full_path)
{
	int	j;

	j = 0;
	if ((*cmd)->has_heredoc)
	{
		if (ft_strcmp((*cmd)->argv[0], "cat") == 0)
		{
			while (j < (*cmd)->lines_heredoc)
			{
				printf("%s\n", (*cmd)->heredoc_text[j]);
				j++;
			}
		}
		free(path);
		free(full_path);
		return(1);
	}
	return (0);
}
