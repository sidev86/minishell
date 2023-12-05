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
	char	*new_directory;

	if ((*cmd)->argc == 1 || (ft_strcmp((*cmd)->argv[1], "~") == 0))
		cd_to_home_directory();
	else if ((*cmd)->argc == 2)
	{
		new_directory = (*cmd)->argv[1];
		cd_to_custom_directory(new_directory);
	}
	else
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Too many arguments", "Error");
	}
	errors_manager(SET_CODE, 0, NULL, NULL);
}

static void	handle_export_errors(char *env_arg, int *var_len, char **var_name)
{
	if (!env_arg)
	{
		errors_manager(SET_CODE, 0, NULL, NULL);
		return ;
	}
	if (!ft_strchr(env_arg, '='))
		*var_len = ft_strlen(env_arg);
	else
		*var_len = ft_strlen(env_arg) - ft_strlen(ft_strchr(env_arg, '='));
	if (*var_len == 0)
		*var_len = 1;
	*var_name = ft_substr(env_arg, 0, *var_len);
	if (check_var_validity(*var_name))
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Not a valid identifier", *var_name);
		return ;
	}
}

void	ft_export(t_command **cmd, t_env_vars ***env_list)
{
	char	*env_arg;
	int		var_len;
	char	*var_name;

	env_arg = (*cmd)->argv[1];
	handle_export_errors(env_arg, &var_len, &var_name);
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
	errors_manager(SET_CODE, 0, NULL, NULL);
	return ;
}
