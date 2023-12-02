#include "minishell.h"

int ft_cmd_builtin(char* cmd)
{
    if (!strcmp(cmd, "echo"))
        return 1;
    else if (!strcmp(cmd, "cd"))
        return 1;
    else if (!strcmp(cmd, "pwd"))
        return 1;
    else if (!strcmp(cmd, "export"))
        return 1;
    else if (!strcmp(cmd, "unset"))
        return 1;
    else if (!strcmp(cmd, "env"))
        return 1;
    //else if (!strcmp(cmd, "exit"))
    //    return 1;
    else
        return 0;
}

int ft_count_environment_vars(char **envp)
{
    int i = 0;
    while (envp[i])
        i++;
    return (i);
}

char **ft_get_environment_vars(char **envp)
{
    char **env;
    int i = 0;
    env = (char**)malloc(sizeof(char*) * ft_count_environment_vars(envp) + 1);
    while (envp[i])
    {
        env[i] = ft_strjoin(envp[i], "\0");
        i++;
    }
    env[i] = NULL;
    return (env);
}

int ft_get_num_cmds(t_tokens *cmd_line, int num_tokens)
{
	int	i = 0; 
	int num_cmds = 0; 
	
	if (cmd_line[i].token)
		num_cmds++;
	while(i < num_tokens)
	{
		if (!strcmp(cmd_line[i].token, "|"))
			num_cmds++;
		i++;
	}
	return (num_cmds);

}

int	ft_get_tokens_in_cmd(t_tokens *cmd_line, int index, int total_tokens)
{
	int	tokens;
	
	tokens = 0;
	while (index < total_tokens)
	{
		if (!strchr(cmd_line[index].token, '|') || (strchr(cmd_line[index].token, '|') && strlen(cmd_line[index].token) > 1))
		{
			tokens++;
			index++;
		}
		else 
			break;	
	}
	return (tokens);
}

void ft_print_all_commands(t_command **command)
{
	t_command *curr;
	int num_cmd = 1;
	int i = 0;
	curr = *command; 
	
	while(curr)
	{
		printf("Command %d\n", num_cmd);
		i = 0;
		while(curr->argv[i])
		{
			printf("%s\n",curr->argv[i]);
			i++;
		}
		num_cmd++;
		curr = curr->next;
	}	


}

void ft_parse(t_tokens* cmd_line, int total_tokens, t_env_vars **env_list, char **envp)
{
	t_command *command;
	t_command *curr_cmd;
	int arg_index;
	int total_cmds;
	int i = 0;
	
	total_cmds = ft_get_num_cmds(cmd_line, total_tokens);
	total_cmds = total_cmds + 1 - 1;
	command = (t_command*)malloc(sizeof(t_command));
	curr_cmd = command;
	curr_cmd->number = 1;
	curr_cmd->num_cmds = total_cmds;
	arg_index = 0; 
	while (arg_index < total_tokens)
	{
		curr_cmd->num_tokens = ft_get_tokens_in_cmd(cmd_line, arg_index, total_tokens);
		curr_cmd->argv = (char**)malloc(sizeof(char*) * curr_cmd->num_tokens + 1);
		curr_cmd->argc = curr_cmd->num_tokens;
		curr_cmd->redir_in = 0; 
		curr_cmd->redir_out = 0;
		if (!curr_cmd->argv)
			printf("Malloc error");
		i = 0;
		while (i < curr_cmd->num_tokens)
		{
			curr_cmd->argv[i] = ft_substr(cmd_line[arg_index + i].token, 0, strlen(cmd_line[arg_index + i].token));
			if (curr_cmd->argv[i][0] == '\\' || !strcmp(curr_cmd->argv[i], ";"))
			{
				printf("Error: detected '\'' or ';' \n");
				return ;
			}
			i++;
		}
		if (ft_cmd_builtin(curr_cmd->argv[0]))
			curr_cmd->is_builtin = 1; 
		else
			curr_cmd->is_builtin = 0;
		curr_cmd->argv[i] = NULL;
		arg_index += curr_cmd->num_tokens + 1;
		if (arg_index < total_tokens)
		{
			curr_cmd->next = (t_command*)malloc(sizeof(t_command));
			curr_cmd->next->prev = (t_command*)malloc(sizeof(t_command));
			if (curr_cmd->number == 1)
				curr_cmd->prev = NULL;
			curr_cmd->next->prev = curr_cmd;
			curr_cmd->next->number = curr_cmd->number + 1;
			curr_cmd = curr_cmd->next;
				
		}
		else
			curr_cmd->next = NULL;
		
	}
	//ft_print_all_commands(&command);  //funzione per testing
	ft_execute(&command, env_list, envp);
	free(command);

}
