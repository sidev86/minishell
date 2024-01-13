/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:27:24 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:27:25 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command_search_path(t_command **cmd, char **envp, t_env_vars **env_list, char **dirs)
{
	int		i;
	char	*path;
	char	*full_path;

	i = 0;
	while (dirs[i])
	{
		path = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(path, (*cmd)->argv[0]);
		if (ft_check_if_heredoc(cmd, path, full_path))
			ft_free_heredoc(cmd, dirs, env_list);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			errors_manager(SET_CODE, 100, NULL, NULL);
			if (execve(full_path, (*cmd)->argv, envp) == -1)
			{
				errors_manager(PRINT, 126, "Execution error\n", "Error");
				exit(126);
			}
			exit(0);
		}
		free(path);
		free(full_path);
		i++;
	}
}

static void	exec_command_direct_path(t_command **cmd, char **envp, t_env_vars **env_list, char *path)
{
	path = (*cmd)->argv[0];
	if (access(path, F_OK | X_OK) == 0)
	{
		(*cmd)->argv[0] = ft_get_cmdname((*cmd)->argv[0]);
		if (execve(path, (*cmd)->argv, envp) == -1)
		{
			errors_manager(SET_CODE, 127, NULL, NULL);
			errors_manager(PRINT, 127, "Execution error", "Error");
		}
		exit(0);
	}
	if ((*cmd)->argv[0][0] == '.' && (*cmd)->argv[0][1] == '/')
	{
		errors_manager(PRINT, 126, "Executable not found\n", (*cmd)->argv[0]);
		exit(126);
	}
	errors_manager(PRINT, 127, "Command not found\n", (*cmd)->argv[0]);
	ft_free_all_commands(cmd);
	ft_free_env_list(env_list);
	exit(127);
}

void	ft_exec_systemcmd(t_command **cmd, char **envp, t_env_vars **env_list)
{
	char	*path;
	char	**dirs;
	int	i;
	
	path = ft_get_path(env_list);
	dirs = 0;
	if (!ft_strchr((*cmd)->argv[0], '/'))
	{
		if (path)
		{
			dirs = ft_split(path, ':');
			exec_command_search_path(cmd, envp, env_list, dirs);
		}
		errors_manager(PRINT, 127, "Command not found\n", (*cmd)->argv[0]);
		ft_free_all_commands(cmd);
		ft_free_env_list(env_list);
		i = 0;
		if (dirs)
		{
			while (dirs[i])
				free(dirs[i++]);
			free(dirs);
		}
		exit(127);
	}
	else
		exec_command_direct_path(cmd, envp, env_list, (*cmd)->argv[0]);
}

void	ft_exec_builtin(t_command **cmd, t_env_vars ***env_list)
{
	if (!ft_strcmp((*cmd)->argv[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp((*cmd)->argv[0], "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp((*cmd)->argv[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp((*cmd)->argv[0], "export"))
		ft_export(cmd, env_list);
	else if (!ft_strcmp((*cmd)->argv[0], "unset"))
		ft_unset(cmd, env_list);
	else if (!ft_strcmp((*cmd)->argv[0], "env"))
		ft_env(env_list);
	if ((*cmd)->num_cmds > 1)
	{
		ft_free_all_commands(cmd);
		ft_free_env_list(*env_list);
	}
	
}
