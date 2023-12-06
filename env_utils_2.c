#include "minishell.h"

void	ft_set_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
	t_env_vars	*curr;

	curr = **env_list;
	while (curr->next)
		curr = curr->next;
	curr->next = malloc(sizeof(t_env_vars));
	curr = curr->next;
	curr->env_str = env_str;
	curr->var = ft_substr(env_str, 0, var_len);
	curr->value = ft_substr(env_str, var_len + 1, ft_strlen(env_str) - var_len
			- 1);
	curr->next = NULL;
}

void	ft_update_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
	t_env_vars	*curr;

	curr = **env_list;
	while (ft_strcmp(curr->var, ft_substr(env_str, 0, var_len)))
		curr = curr->next;
	curr->env_str = env_str;
	curr->var = ft_substr(env_str, 0, var_len);
	curr->value = ft_substr(env_str, var_len + 1, ft_strlen(env_str) - var_len
			- 1);
}

t_env_vars	*find_env_var_node(t_env_vars ***env_list, char *env_str,
		int var_len)
{
	t_env_vars	*curr;

	curr = **env_list;
	while (curr != NULL && ft_strcmp(curr->var, \
	ft_substr(env_str, 0, var_len)) != 0)
		curr = curr->next;
	return (curr);
}

void	remove_env_var_node(t_env_vars ***env_list, t_env_vars *node_to_remove)
{
	t_env_vars	*curr;

	if (node_to_remove == NULL)
		return ;
	if (**env_list == node_to_remove)
		**env_list = node_to_remove->next;
	else
	{
		curr = **env_list;
		while (curr != NULL && curr->next != node_to_remove)
			curr = curr->next;
		if (curr != NULL)
			curr->next = node_to_remove->next;
	}
	free(node_to_remove);
}

void	ft_remove_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
	t_env_vars	*node_to_remove;

	node_to_remove = find_env_var_node(env_list, env_str, var_len);
	remove_env_var_node(env_list, node_to_remove);
}
