#include "minishell.h"

int	handle_end_token(char *input_line, t_command **cmd, int *end_token_index)
{
	int		last_end_token_index;

	last_end_token_index = (*cmd)->heredoc_counter - 1;
	if (strcmp(input_line, (*cmd)->end_tokens[*end_token_index]) == 0)
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

void	process_heredoc_line(t_command **cmd, char *input_line, int *line_count)
{
	int		i;
	int		j;
	char *output = (char *)malloc(strlen(input_line) * 100);

	i = 0;
	j = 0;
	while (input_line[i])
	{
		if (input_line[i] == '$' && is_alphanumeric(input_line[i + 1]))
		{
		    i++;
		    extract_and_handle(output, &j, input_line, &i);
		}
		else
		    output[j++] = input_line[i++];
	}
    	output[j] = '\0';
    	(*line_count)++;
    	(*cmd)->heredoc_text = (char **)realloc((*cmd)->heredoc_text, (*line_count) * sizeof(char *));
    	(*cmd)->heredoc_text[(*line_count) - 1] = strdup(output);
    	free(output);
}

void	handle_input_condition(t_command **cmd, char *input_line, int *end_token_index, int *line_count)
{
	int		last_end_token_index;
	
	last_end_token_index = (*cmd)->heredoc_counter - 1;
	if (last_end_token_index == 0)
		process_heredoc_line(cmd, input_line, line_count);
	else if (last_end_token_index > 0 && *end_token_index == last_end_token_index)
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
		if(handle_end_token(input_line, cmd, &end_token_index))	
			break;	
		handle_input_condition(cmd, input_line, &end_token_index, &line_count);
		free(input_line);
	}
}

