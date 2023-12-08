#include "minishell.h"

static void	exec_command_in_path(char *cmd_name, char **dirs, char **envp,
		t_command **cmd)
{
	int		i;
	char	*path;
	char	*full_path;

	i = 0;
	while (dirs[i])
	{
		path = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(path, cmd_name);
		ft_check_if_heredoc(cmd);
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

static void	exec_command_direct(t_command **cmd, char **envp, char *path)
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
	exit(127);
}

void	ft_exec_systemcmd(t_command **cmd, char **envp, t_env_vars **env_list)
{
	char	*path;
	char	**dirs;

	path = ft_get_path(env_list);
	if (!ft_strchr((*cmd)->argv[0], '/'))
	{
		if (path)
		{
			dirs = ft_split(path, ':');
			exec_command_in_path((*cmd)->argv[0], dirs, envp, cmd);
		}
		errors_manager(PRINT, 127, "Command not found\n", path);
		exit(127);
	}
	else
		exec_command_direct(cmd, envp, (*cmd)->argv[0]);
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
}
