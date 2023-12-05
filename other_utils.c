#include "minishell.h"

int ft_cmd_builtin(char* cmd)
{
    if (!ft_strcmp(cmd, "echo"))
        return 1;
    else if (!ft_strcmp(cmd, "cd"))
        return 1;
    else if (!ft_strcmp(cmd, "pwd"))
        return 1;
    else if (!ft_strcmp(cmd, "export"))
        return 1;
    else if (!ft_strcmp(cmd, "unset"))
        return 1;
    else if (!ft_strcmp(cmd, "env"))
        return 1;
    else
        return 0;
}

char	*ft_get_cmdname(char *str)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	while (str[i])
		i++;
	i--;
	j = i;
	while (str[j] != '/')
		j--;
	j++;
	cmd = ft_substr(str, j, i - j + 1);
	return (cmd);
}

int	ft_get_total_cmds(t_command **cmd)
{
	int	total;

	total = 0;
	while (*cmd)
	{
		total++;
		(*cmd) = (*cmd)->next;
	}
	return (total);
}

char	*ft_get_path(t_env_vars **env_list)
{
	t_env_vars	*curr;

	curr = *env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->var, "PATH"))
			return (curr->value);
		if (curr->next)
			curr = curr->next;
		else
			break ;
	}
	return (NULL);
}


void	ft_handle_quotes_alltokens(t_command **cmd)
{
	int	i;

	i = 0;
	while (i < (*cmd)->argc)
	{
		if ((*cmd)->argv[i])
		{
			(*cmd)->argv[i] = handle_quotes((*cmd)->argv[i]);
		}
		i++;
	}
}



