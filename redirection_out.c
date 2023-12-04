#include "minishell.h"
#include <fcntl.h>


int ft_redir_output_overwrite(char *filename)
{
	int original_fd = dup(STDOUT_FILENO);
	//printf("redirection overwrite %s\n", filename);
	if (filename)
	{
		//printf("got filename\n");
		int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		
		if (file == -1)
		{
			//printf("erroreeeee\n");
			//close(file);
			errors_manager(SET_CODE, 1, NULL, NULL);
			errors_manager(PRINT, 1, "Can't open or create file\n", filename);
			return (-1);
		}
		//printf("file opended?\n");
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	return (original_fd);
}

int ft_redir_output_append(char *filename)
{
	int original_fd = dup(STDOUT_FILENO);
	//printf("redirection with append\n"); 
	if (filename)
	{
		int file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (file == -1)
		{
			errors_manager(SET_CODE, 1, NULL, NULL);
			errors_manager(PRINT, 1, "Can't open or create file\n", filename);
			return (-1);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	
	return (original_fd);
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


void ft_empty_out_other(t_command **cmd)
{
	int	i = 0; 
	int	last_redir;
	int	num_redir = 0;
	int	file;
	last_redir = (*cmd)->num_redirs - 1; 
	
	while (i < (*cmd)->num_tokens)
	{
		if ((*cmd)->argv[i])
		{
			if (!ft_strcmp((*cmd)->argv[i], ">"))
			{
				file = open((*cmd)->argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (file == -1)
				{
					errors_manager(SET_CODE, 1, NULL, NULL);
					errors_manager(PRINT, 1, "Can't open or create file\n", "Error");
					return ;
				}
				close(file);
			}
			if (!ft_strcmp((*cmd)->argv[i], ">") || !ft_strcmp((*cmd)->argv[i], ">>"))
			{
				num_redir++;
				(*cmd)->argv[i] = NULL;
				if ((*cmd)->argv[i+1])
					(*cmd)->argv[i+1] = NULL;
				i++;
			}
		}
		if (num_redir == last_redir)
			break;
		i++;
	}
}



void ft_check_output_redirs(t_command **cmd)
{
	int	i; 
	int fd_stdout = -1;
	
	i = 0; 
	
	(*cmd)->num_redirs = ft_get_out_redirections(cmd);
	if ((*cmd)->num_redirs > 0)
		i = ft_last_out_redir(cmd);
	if ((*cmd)->argv[i])
	{
		if (!ft_strcmp((*cmd)->argv[i], ">") || !ft_strcmp((*cmd)->argv[i], ">>"))
		{
			(*cmd)->redir_out = 1;
			if (!ft_strcmp((*cmd)->argv[i], ">")) 
				fd_stdout = ft_redir_output_overwrite((*cmd)->argv[i + 1]);
			else if(!ft_strcmp((*cmd)->argv[i], ">>"))
				fd_stdout = ft_redir_output_append((*cmd)->argv[i+1]);
			//printf("working??\n");
			(*cmd)->argv[i] = NULL; 
			
			if ((*cmd)->argv[i + 1])
				(*cmd)->argv[i + 1] = NULL;
			if ((*cmd)->num_redirs > 1)
				ft_empty_out_other(cmd);
			//printf("here?\n");
			
		}
	}
	i++;
		
	
	(*cmd)->fd_terminal = fd_stdout;
	//printf("Number of out redirections in command0 = %d\n", (*cmd)->num_redirs);
}
