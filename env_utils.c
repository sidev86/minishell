/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:39:46 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:39:48 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_env_list(t_env_vars **first, char **envp)
{
	int			i;
	t_env_vars	*curr;

	i = 0;
	if (i == 0 && envp[i])
		*first = malloc(sizeof(t_env_vars));
	if (!(*first))
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
	curr = *first;
	while (envp[i])
	{
		curr->env_str = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		curr->var = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		curr->value = ft_substr(envp[i], ft_strlen(envp[i])
				- ft_strlen(ft_strchr(envp[i], '=')) + 1, envp[i]
				- ft_strchr(envp[i], '='));
		if (envp[i + 1])
		{
			curr->next = malloc(sizeof(t_env_vars));
			curr = curr->next;
		}
		else
			curr->next = NULL;
		i++;
	}
}

int	ft_env_var_exists(t_env_vars ***env_list, char *var)
{
	t_env_vars	*curr;

	curr = **env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->var, var))
			return (1);
		curr = curr->next;
	}
	return (0);
}

char	*ft_get_env_var_value(t_env_vars **env_list, char *var)
{
	t_env_vars	*curr;

	curr = *env_list;
	while (curr)
	{
		if (ft_strcmp(curr->var, var))
			curr = curr->next;
		else
			return (curr->value);
	}
	return (NULL);
}
