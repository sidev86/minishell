/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:25:58 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:26:00 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo_arguments(t_command *cmd, int *i)
{
	while (*i < cmd->argc)
	{
		if (cmd->argv[*i])
		{
			printf("%s", cmd->argv[*i]);
			if (*i < cmd->argc - 1 && cmd->argv[*i + 1])
				printf(" ");
		}
		(*i)++;
	}
}

void	ft_echo(t_command **cmd)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if ((*cmd)->argv[i])
	{
		if (i < (*cmd)->argc && ft_strcmp((*cmd)->argv[i], "-n") == 0)
		{
			no_newline = 1;
			i++;
		}
	}
	print_echo_arguments(*cmd, &i);
	if (i < (*cmd)->argc || no_newline == 0)
		printf("\n");
	errors_manager(SET_CODE, 0, NULL, NULL);
	//if ((*cmd)->num_cmds > 1)
	//	exit(0);
}

void	ft_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		errors_manager(SET_CODE, 130, NULL, NULL);
		return ;
	}
	printf("%s\n", current_dir);
	errors_manager(SET_CODE, 0, NULL, NULL);
	free(current_dir);
	return ;
}

void	ft_unset(t_command **cmd, t_env_vars ***env_list)
{
	char	*env_arg;
	int		var_len;

	env_arg = NULL;
	if ((*cmd)->argv[1])
		env_arg = ft_substr((*cmd)->argv[1], 0, ft_strlen((*cmd)->argv[1]));
	if (!env_arg)
	{
		errors_manager(SET_CODE, 0, NULL, NULL);
		return ;
	}
	var_len = ft_strlen(env_arg);
	if (ft_env_var_exists(env_list, env_arg)
		&& env_arg != NULL)
	{
		ft_remove_env_var(env_list, env_arg, var_len);
	}
	errors_manager(SET_CODE, 0, NULL, NULL);
	free(env_arg);
	return ;
}

void	ft_env(t_env_vars ***env_list)
{
	t_env_vars	*curr;

	curr = **env_list;
	while (curr)
	{
		printf("%s\n", curr->env_str);
		curr = curr->next;
	}
	errors_manager(SET_CODE, 0, NULL, NULL);
	return ;
}
