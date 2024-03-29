/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:39:23 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:39:25 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_and_handle_var_validity(char **var_name)
{
	if (check_var_validity(*var_name))
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Not a valid identifier\n", *var_name);
		return (1);
	}
	return (0);
}

static int	handle_export_errors(char *env_arg, int *var_len)
{
	char	*var_name;
	int		var_check;

	var_check = 0;
	if (!env_arg)
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		return (1);
	}
	if (!ft_strchr(env_arg, '='))
	{
		*var_len = ft_strlen(env_arg);
	}
	else
		*var_len = ft_strlen(env_arg) - ft_strlen(ft_strchr(env_arg, '='));
	if (*var_len == 0)
		*var_len = 1;
	var_name = ft_substr(env_arg, 0, *var_len);
	var_check = check_and_handle_var_validity(&var_name);
	free(var_name);
	return (var_check);
}

static void	ft_handle_env_var(t_env_vars ***env_list, char *env_arg,
		int var_len)
{
	char	*var;

	var = ft_substr(env_arg, 0, var_len);
	if (!ft_env_var_exists(env_list, var) && env_arg != NULL)
	{
		ft_set_env_var(env_list, env_arg, var_len);
	}
	else if (ft_env_var_exists(env_list, var) && env_arg != NULL)
	{
		ft_update_env_var(env_list, env_arg, var_len);
	}
	free(var);
}

void	ft_export(t_command **cmd, t_env_vars ***env_list)
{
	int		var_len;
	int		i;
	char	*env_arg;

	i = 1;
	if ((*cmd)->argc > 1)
	{
		while ((*cmd)->argv[i])
		{
			env_arg = ft_substr((*cmd)->argv[i], 0, ft_strlen((*cmd)->argv[i]));
			if (handle_export_errors(env_arg, &var_len))
			{
				free(env_arg);
				return ;
			}
			ft_handle_env_var(env_list, env_arg, var_len);
			i++;
			free(env_arg);
		}
	}
	errors_manager(SET_CODE, 0, NULL, NULL);
	return ;
}
