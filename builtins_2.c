/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:39:10 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:39:13 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

static void	cd_to_home_directory(void)
{
	char	*home_directory;

	home_directory = getenv("HOME");
	if (home_directory == NULL)
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Variable HOME not set\n", "Error");
		return ;
	}
	if (chdir(home_directory) == -1)
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "No such file or directory\n", home_directory);
		return ;
	}
}

static int	cd_to_custom_directory(char *directory)
{
	if (chdir(directory) == -1)
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "No such file or directory\n", directory);
		return (1);
	}
	else
		return (0);
}

void	ft_cd(t_command **cmd)
{
	char	*cmd_name;

	if ((*cmd)->argc == 1 || (ft_strcmp((*cmd)->argv[1], "~") == 0))
		cd_to_home_directory();
	else if ((*cmd)->argc == 2)
	{
		cmd_name = (*cmd)->argv[1];
		if (cd_to_custom_directory(cmd_name))
			return ;
	}
	else
	{
		cmd_name = (*cmd)->argv[0];
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Too many arguments\n", cmd_name);
		return ;
	}
	errors_manager(SET_CODE, 0, NULL, NULL);
}

void	ft_exit(t_command **cmd, t_env_vars ***env_list)
{
	int	e_code;

	e_code = 0;
	if ((*cmd)->num_tokens > 2)
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Too many arguments\n", "exit");
		if ((*cmd)->num_cmds > 1)
			exit(1);
		return ;
	}
	else if ((*cmd)->num_tokens > 1)
		e_code = ft_atoi((*cmd)->argv[1]);
	errors_manager(SET_CODE, e_code, NULL, NULL);
	ft_free_all_commands(cmd);
	ft_free_env_list(*env_list);
	exit(e_code);
}
