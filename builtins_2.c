#include "minishell.h"

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

static void	cd_to_custom_directory(char *directory)
{
	if (chdir(directory) == -1)
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "No such file or directory\n", directory);
		return ;
	}
}

void	ft_cd(t_command **cmd)
{
	char	*cmd_name;

	if ((*cmd)->argc == 1 || (ft_strcmp((*cmd)->argv[1], "~") == 0))
		cd_to_home_directory();
	else if ((*cmd)->argc == 2)
	{
		cmd_name = (*cmd)->argv[1];
		cd_to_custom_directory(cmd_name);
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

static int	handle_export_errors(char *env_arg, int *var_len)
{
	char *var_name;
	if (!env_arg)
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		return 1;
	}
	if (!ft_strchr(env_arg, '='))
	{
		*var_len = ft_strlen(env_arg);
		ft_strcat(env_arg, "=NULL");
	}
	else
		*var_len = ft_strlen(env_arg) - ft_strlen(ft_strchr(env_arg, '='));
	if (*var_len == 0)
		*var_len = 1;
	var_name = ft_substr(env_arg, 0, *var_len);
	if (check_var_validity(var_name))
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Not a valid identifier\n", var_name);
		free(var_name);
		return 1;
	}
	free(var_name);
	return 0;
}

void	ft_export(t_command **cmd, t_env_vars ***env_list)
{
	char	*env_arg;
	int		var_len;
	int		i;

	i = 1;
	
	if ((*cmd)->argc > 1)
	{
		while ((*cmd)->argv[i])
		{
			env_arg = (*cmd)->argv[i];
			if (handle_export_errors(env_arg, &var_len))
				return ;
			if (!ft_env_var_exists(env_list, ft_substr(env_arg, 0, var_len))
				&& env_arg != NULL)
			{
				ft_set_env_var(env_list, env_arg, var_len);
			}
			else if (ft_env_var_exists(env_list, ft_substr(env_arg, 0, var_len))
				&& env_arg != NULL)
			{
				ft_update_env_var(env_list, env_arg, var_len);
			}
			i++;
		}
	}
	errors_manager(SET_CODE, 0, NULL, NULL);
	return ;
}
