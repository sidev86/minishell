#include "minishell.h"

void	ft_set_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
	t_env_vars	*curr;

	curr = **env_list;
	while (curr->next)
		curr = curr->next;
	curr->next = malloc(sizeof(t_env_vars));
	curr = curr->next;
	curr->env_str = ft_substr(env_str, 0, ft_strlen(env_str));
	curr->var = ft_substr(env_str, 0, var_len);
	curr->value = ft_substr(env_str, var_len + 1, ft_strlen(env_str) - var_len
			- 1);
	curr->next = NULL;
}

void	ft_update_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
	t_env_vars	*curr;
	char		*var_str;
	
	curr = **env_list;
	var_str = ft_substr(env_str, 0, var_len);
	while (ft_strcmp(curr->var, var_str))
		curr = curr->next;
	if (curr->var)
		free(curr->var);
	if (curr->value)
		free(curr->value);
	if (curr->env_str)
		free(curr->env_str);
	curr->env_str = ft_substr(env_str, 0, ft_strlen(env_str));
	curr->var = ft_substr(env_str, 0, var_len);
	curr->value = ft_substr(env_str, var_len + 1, ft_strlen(env_str) - var_len
			- 1);
	free(var_str);
}

static t_env_vars	*find_env_var_node(t_env_vars ***env_list, char *env_str,
		int var_len)
{
	t_env_vars	*curr;
	char		*var;

	curr = **env_list;
	var = ft_substr(env_str, 0, var_len);
	while (curr != NULL && (ft_strcmp(curr->var, var) != 0))
		curr = curr->next;
	free(var);
	return (curr);
}

static void	remove_env_var_node(t_env_vars ***env_list,
		t_env_vars *node_to_remove)
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
	free(node_to_remove->env_str);
	free(node_to_remove->var);
	free(node_to_remove->value);
	free(node_to_remove);
}

void	ft_remove_env_var(t_env_vars ***env_list, char *env_str, int var_len)
{
	t_env_vars	*node_to_remove;

	node_to_remove = find_env_var_node(env_list, env_str, var_len);
	remove_env_var_node(env_list, node_to_remove);
}
