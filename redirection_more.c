#include "minishell.h"


int ft_get_in_redirections(t_command **cmd)
{
	int i = 0; 
	int redirs = 0; 
	
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if (!ft_strcmp((*cmd)->argv[i], "<") || !ft_strcmp((*cmd)->argv[i], "<<"))
			{
				redirs++;
				if(!ft_strcmp((*cmd)->argv[i], "<<"))
				{
					(*cmd)->heredoc_counter++;
					(*cmd)->end_tokens = realloc((*cmd)->end_tokens, sizeof(char) * (*cmd)->heredoc_counter);
					(*cmd)->end_tokens[((*cmd)->heredoc_counter) - 1] = ft_strdup((*cmd)->argv[i + 1]);
				}
			}
		}
		i++;
	}
	return (redirs);
}


int ft_last_in_redir(t_command **cmd)
{
	int i = 0; 
	int redir_num = 0; 
	
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if (!ft_strcmp((*cmd)->argv[i], "<") || !ft_strcmp((*cmd)->argv[i], "<<"))
				redir_num++; 
		}
		if (redir_num == (*cmd)->num_redirs)
				break;
		i++;
	}
	return (i);

}



int ft_get_out_redirections(t_command **cmd)
{
	int i = 0; 
	int redirs = 0; 
	
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if ((!ft_strcmp((*cmd)->argv[i], ">") || !ft_strcmp((*cmd)->argv[i], ">>")) && (*cmd)->argv[i])
				redirs++;	
		}
		i++;
	}
	return (redirs);
}


int ft_last_out_redir(t_command **cmd)
{
	int i = 0; 
	int redir_num = 0; 
	
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if (!ft_strcmp((*cmd)->argv[i], ">") || !ft_strcmp((*cmd)->argv[i], ">>"))
				redir_num++; 
		}
		if (redir_num == (*cmd)->num_redirs)
			break;
		i++;
	}
	return (i);

}

