/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:29:18 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:29:19 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	*ft_get_cmdname(char *str)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	while (str[i])
		i++;
	i--;
	j = i;
	while (str[j] != '/')
		j--;
	j++;
	cmd = ft_substr(str, j, i - j + 1);
	return (cmd);
}

char	*ft_get_path(t_env_vars **env_list)
{
	t_env_vars	*curr;

	curr = *env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->var, "PATH"))
			return (curr->value);
		if (curr->next)
			curr = curr->next;
		else
			break ;
	}
	return (NULL);
}

void ft_handle_quotes_single_token(t_command **cmd, t_env_vars **env_list, int i)
{
	char	*str;
	
	str = handle_quotes((*cmd)->argv[i], env_list);
	(*cmd)->argv[i] = ft_realloc((*cmd)->argv[i], ft_strlen((*cmd)->argv[i]) + 1, ft_strlen(str) + 1);
	ft_strcpy((*cmd)->argv[i], str);
	free(str);
}

void	ft_handle_quotes_alltokens(t_command **cmd, t_env_vars **env_list)
{
	int		i;
	char	*str;

	i = 0;
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			str = handle_quotes((*cmd)->argv[i], env_list);
			(*cmd)->argv[i] = ft_realloc((*cmd)->argv[i], ft_strlen((*cmd)->argv[i]) + 1, ft_strlen(str) + 1);
			ft_strcpy((*cmd)->argv[i], str);
			free(str);
		}
		i++;
	}
}

void	handle_exit_code(char *output, int *j, char *variabile)
{
	int		i;
	int		e_code;
	char	*code_str;

	i = 0;
	e_code = 0;
	if (variabile[i] == '?')
	{
		e_code = errors_manager(GET_CODE, 0, NULL, NULL);
		code_str = ft_itoa(e_code);
		ft_strcpy(output, code_str);
		(*j) += ft_strlen(code_str);
		if (variabile[i + 1] != ' ' && variabile[i + 1])
		{
			while (variabile[i + 1] != ' ' && variabile[i + 1])
				output[(*j)++] = variabile[++i];
		}
		free(code_str);
	}
}
