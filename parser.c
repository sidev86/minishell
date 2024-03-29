/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:41:49 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:41:50 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_first_cmd_node(t_command **command, t_tokens *cmd_line,
		int total_tokens)
{
	(*command) = (t_command *)malloc(sizeof(t_command));
	if (!(*command))
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
	(*command)->number = 1;
	(*command)->num_cmds = ft_get_num_cmds(cmd_line, total_tokens);
	(*command)->prev = NULL;
	(*command)->last_exit_code = errors_manager(GET_CODE, 0, NULL, NULL);
}

static void	ft_set_cmd_parameters(t_command **curr_cmd, t_command **cmd)
{
	(*curr_cmd)->argv = (char **)malloc(sizeof(char *)
			* ((*curr_cmd)->num_tokens + 1));
	if (!(*curr_cmd)->argv)
		ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
	(*curr_cmd)->end_tokens = NULL;
	(*curr_cmd)->heredoc_text = NULL;
	(*curr_cmd)->lines_heredoc = 0;
	(*curr_cmd)->heredoc_counter = 0;
	(*curr_cmd)->argc = (*curr_cmd)->num_tokens;
	(*curr_cmd)->redir_in = 0;
	(*curr_cmd)->redir_out = 0;
	(*curr_cmd)->has_heredoc = 0;
	(*curr_cmd)->fd_terminal = STDOUT_FILENO;
	(*curr_cmd)->fd_stdinput = STDIN_FILENO;
	(*curr_cmd)->num_cmds = (*cmd)->num_cmds;
	(*curr_cmd)->last_exit_code = errors_manager(GET_CODE, 0, NULL, NULL);
}

static void	ft_set_next_prev_nodes(t_command **curr_cmd, int arg_index,
		int total_tokens)
{
	if (arg_index < total_tokens)
	{
		(*curr_cmd)->next = (t_command *)malloc(sizeof(t_command));
		if (!(*curr_cmd)->next)
			ft_putstr_fd("Error: memory allocation error!", STDERR_FILENO);
		(*curr_cmd)->next->prev = NULL;
		if ((*curr_cmd)->number == 1)
			(*curr_cmd)->prev = NULL;
		(*curr_cmd)->next->prev = (*curr_cmd);
		(*curr_cmd)->next->number = (*curr_cmd)->number + 1;
		(*curr_cmd) = (*curr_cmd)->next;
	}
	else
		(*curr_cmd)->next = NULL;
}

static void	ft_set_cmd_type(t_command **curr_cmd)
{
	if (ft_cmd_builtin((*curr_cmd)->argv[0]))
		(*curr_cmd)->is_builtin = 1;
	else
		(*curr_cmd)->is_builtin = 0;
}

void	ft_parse(t_tokens *cmd_line, int total_tokens, t_env_vars **env_list,
		char **envp)
{
	t_command	*command;
	t_command	*curr_cmd;
	int			arg_index;
	int			i;

	arg_index = 0;
	ft_init_first_cmd_node(&command, cmd_line, total_tokens);
	curr_cmd = command;
	while (arg_index < total_tokens)
	{
		curr_cmd->num_tokens = ft_get_tokens_in_cmd(cmd_line, arg_index,
				total_tokens);
		if (curr_cmd->num_tokens == 0)
			return ;
		ft_set_cmd_parameters(&curr_cmd, &command);
		i = ft_put_tokens_in_cmd(&curr_cmd, cmd_line, arg_index);
		ft_set_cmd_type(&curr_cmd);
		ft_set_args(&curr_cmd, &arg_index, i);
		ft_set_next_prev_nodes(&curr_cmd, arg_index, total_tokens);
	}
	if (ft_check_tokens_validity(&command, cmd_line, total_tokens))
		return ;
	ft_free_tokens(cmd_line, total_tokens);
	ft_execute(&command, env_list, envp);
	ft_free_all_commands(&command);
}
