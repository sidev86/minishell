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
    else if (!strcmp(cmd, "exit"))
        return 1;
    else
        return 0;
}

void ft_parse(char** cmd_line, int num_tokens)
{
    t_command *command;
    int arg_index;
    command = NULL; 
    command = (t_command*)malloc(sizeof(t_command));
    
    arg_index = 0; 
    //printf("Number of tokensss = %d\n", num_tokens);
     
    command->argv = (char**)malloc(sizeof(char*) * num_tokens + 1);
    command->argc = num_tokens;
    if (!command->argv)
        printf("Malloc error");
    command->is_builtin = 0;
    while (arg_index < num_tokens)
    {
        command->argv[arg_index] = ft_substr(cmd_line[arg_index], 0, strlen(cmd_line[arg_index]));
        //printf("token= %s\n", command->argv[arg_index]);
        arg_index++;
    }

    if (ft_cmd_builtin(command->argv[0]))
        command->is_builtin = 1; 
    command->argv[num_tokens] = NULL;

    ft_execute(&command);

    //if (!ft_cmd_builtin(command->argv[0]) && !ft_cmd_in_path(command->argv[0]))
    //    perror("Command not found");
}