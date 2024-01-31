/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <sibrahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:40:54 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/26 12:13:08 by sibrahim         ###   ########.fr       */
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
		t_env_vars **env_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(*env_list)->output = 0;
	allocate_heredoc_output(input_line, env_list);
	while (input_line[i])
	{
		if (input_line[i] == '$' && is_alphanumeric(input_line[i + 1]))
		{
			i++;
			extract_and_handle(&j, input_line, &i, env_list);
		}
		else
			(*env_list)->output[j++] = input_line[i++];
	}
	(*env_list)->output[j] = '\0';
	(*cmd)->line_count++;
	allocate_heredoc_text(cmd);
	(*cmd)->heredoc_text[(*cmd)->line_count
		- 1] = ft_strdup((*env_list)->output);
	(*cmd)->lines_heredoc = (*cmd)->line_count;
	free((*env_list)->output);
}

static void	handle_input_condition(t_command **cmd, char *input_line,
		int *end_token_index, t_env_vars **env_list)
{
	int	last_end_token_index;

	last_end_token_index = (*cmd)->heredoc_counter - 1;
	if (last_end_token_index == 0)
		process_heredoc_line(cmd, input_line, env_list);
	else if (last_end_token_index > 0
		&& *end_token_index == last_end_token_index)
	{
		if (!(*cmd)->skip_terminator)
			(*cmd)->skip_terminator = 1;
		else
			process_heredoc_line(cmd, input_line, env_list);
	}
}

void	ft_heredoc(t_command **cmd, t_env_vars **env_list)
{
	char	*input_line;
	int		end_token_index;

	end_token_index = 0;
	(*cmd)->skip_terminator = 0;
	(*cmd)->line_count = 0;
	ft_sigint_checker(SET_CODE, 0);
	while (1)
	{
		input_line = readline("> ");
		ft_check_heredoc_signal(cmd, env_list);
		if (!input_line)
		{
			ft_putstr_fd("\nHeredoc interrotto.\n", STDERR_FILENO);
			break ;
		}
		if (handle_end_token(input_line, cmd, &end_token_index))
		{
			(*cmd)->lines_heredoc = (*cmd)->line_count;
			break ;
		}
		handle_input_condition(cmd, input_line, &end_token_index, env_list);
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
		return (1);
	}
	return (0);
}
