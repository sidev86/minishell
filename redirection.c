#include "minishell.h"
#include <fcntl.h>

int ft_redir_output_overwrite(char *filename)
{
	int original_fd = dup(STDOUT_FILENO);
	//printf("redirection overwrite\n");
	if (filename)
	{
		//printf("got filename\n");
		int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file == -1)
			exit(2);
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
			exit(2);
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	
	return (original_fd);
}

int ft_get_num_redirections(t_command **cmd)
{
	int i = 0; 
	int redirs = 0; 
	
	while ((*cmd)->argv[i])
	{
		if (!strcmp((*cmd)->argv[i], ">") || !strcmp((*cmd)->argv[i], ">>"))
		{
			redirs++;
		}
		i++;
	}
	return (redirs);
}


int ft_goto_last_redir(t_command **cmd)
{
	int i = 0; 
	int redir_num = 0; 
	
	while ((*cmd)->argv[i])
	{
		if (!strcmp((*cmd)->argv[i], ">") || !strcmp((*cmd)->argv[i], ">>"))
			redir_num++; 
		if (redir_num == (*cmd)->num_redirs)
			break;
		i++;
	}
	return (i);

}

void ft_empty_other(t_command **cmd)
{
	int	i = 0; 
	int	last_redir;
	int	num_redir = 0;
	int	file;
	last_redir = (*cmd)->num_redirs - 1; 
	
	while ((*cmd)->argv[i])
	{
		if ((!strcmp((*cmd)->argv[i], ">") || !strcmp((*cmd)->argv[i], ">>")) && (*cmd)->argv[i+1])
		{
			if (!strcmp((*cmd)->argv[i], ">"))
				file = open((*cmd)->argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			num_redir++;
			if (!strcmp((*cmd)->argv[i], ">"))
				close(file);
			(*cmd)->argv[i] = NULL;
			(*cmd)->argv[i+1] = NULL;
			i++;
		}
		if (num_redir == last_redir)
			break;
		i++;
	}
}

void ft_check_for_redirections(t_command **cmd)
{
	int	i; 
	int fd_stdout = -1;
	
	i = 0; 
	while ((*cmd)->argv[i] != NULL)
	{
		(*cmd)->num_redirs = ft_get_num_redirections(cmd);
		//printf("Number of redirections in command = %d\n", (*cmd)->num_redirs);
		if ((*cmd)->num_redirs > 0)
			i = ft_goto_last_redir(cmd);
		if (!strcmp((*cmd)->argv[i], ">") || !strcmp((*cmd)->argv[i], ">>"))
		{
			if (!strcmp((*cmd)->argv[i], ">")) 
				fd_stdout = ft_redir_output_overwrite((*cmd)->argv[i + 1]);
			else if(!strcmp((*cmd)->argv[i], ">>"))
				fd_stdout = ft_redir_output_append((*cmd)->argv[i+1]);
			(*cmd)->argv[i] = NULL; 
			if ((*cmd)->argv[i + 1])
				(*cmd)->argv[i + 1] = NULL;
			if ((*cmd)->num_redirs > 1)
				ft_empty_other(cmd);
		}	
		else if (!strcmp((*cmd)->argv[i], "<"))
			printf("%d° token : redir input\n", i + 1);
		i++;
	}
	(*cmd)->fd_terminal = fd_stdout;
}
