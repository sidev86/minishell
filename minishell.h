/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <sibrahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:10 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/26 15:09:12 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GET_CODE 0
# define SET_CODE 1
# define PRINT 2

# include "libft/libft.h"
# include <fcntl.h>
# include <malloc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_tokens
{
	char				*token;
	int					is_symbol;
	int					in_quotes;
}						t_tokens;

typedef struct s_command
{
	int					argc;
	char				**argv;
	char				**envp;
	char				**heredoc_text;
	char				**end_tokens;
	int					skip_terminator;
	int					lines_heredoc;
	int					has_heredoc;
	int					heredoc_counter;
	int					is_builtin;
	int					fd_terminal;
	int					fd_stdinput;
	int					num_redirs;
	int					num_tokens;
	int					number;
	int					num_cmds;
	int					redir_out;
	int					redir_in;
	int					last_exit_code;
	int					line_count;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_env_vars
{
	char				*env_str;
	char				*var;
	char				*value;
	struct s_env_vars	*next;
	char				*output;
}						t_env_vars;

// STRING FUNCTIONS
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcat(char *dest, char *src);
char					*ft_strcpy(char *s1, const char *s2);
char					*ft_itoa(int n);

// BUILTINS
void					ft_echo(t_command **cmd);
void					ft_cd(t_command **cmd);
void					ft_pwd(void);
void					ft_export(t_command **cmd, t_env_vars ***env_list);
void					ft_unset(t_command **cmd, t_env_vars ***env_list);
void					ft_env(t_env_vars ***env_list);
void					ft_exit(t_command **cmd, t_env_vars ***env_list);
int						ft_cmd_builtin(char *cmd);

// SHELL CORE
void					ft_lex(char *input, t_env_vars **env_list, char **envp);
void					ft_parse(t_tokens *cmd_line, int num_tokens,
							t_env_vars **env_list, char **envp);
void					ft_execute(t_command **cmd, t_env_vars **env_list,
							char **envp);

// ENV LIST
void					ft_create_env_list(t_env_vars **first, char **envp);
int						ft_env_var_exists(t_env_vars ***env_list, char *var);
void					ft_set_env_var(t_env_vars ***env_list, char *env_str,
							int var_len);
void					ft_update_env_var(t_env_vars ***env_list, char *env_str,
							int var_len);
void					ft_remove_env_var(t_env_vars ***env_list, char *env_str,
							int var_len);
char					*ft_get_env_var_value(t_env_vars **env_list, char *var);

// LEXER
int						ft_count_tokens(char *input);
int						ft_get_token_len(char *input, int i);

// PARSING
int						ft_get_num_cmds(t_tokens *cmd_line, int num_tokens);
int						ft_get_tokens_in_cmd(t_tokens *cmd_line, int index,
							int total_tokens);
int						ft_put_tokens_in_cmd(t_command **curr_cmd,
							t_tokens *cmd_line, int arg_index);
void					ft_set_args(t_command **curr_cmd, int *arg_index,
							int i);
int						ft_check_tokens_validity(t_command **cmd,
							t_tokens *cmd_line, int total_tokens);

// REDIRS
int						ft_last_out_redir(t_command **cmd);
int						ft_get_in_redirections(t_command **cmd);
int						ft_last_in_redir(t_command **cmd);
void					ft_empty_out_other(t_command **cmd);

// EXECUTOR
void					ft_exec_builtin(t_command **cmd,
							t_env_vars ***env_list);
void					ft_exec_systemcmd(t_command **cmd, char **envp,
							t_env_vars **env_list);
void					ft_execute_in_child(t_command **curr_cmd, int *fd_pipe,
							t_env_vars **env_list, char **envp);
void					ft_in_child(t_command **curr_cmd, int *fd_pipe,
							t_env_vars **env_list, char **envp);
// ERRORS
int						errors_manager(int action, int code, char *msg,
							char *arg);
int						ft_wrong_pipe_token(char *input);

// CHECKERS
int						check_var_validity(char *arg);
void					ft_check_output_redirs(t_command **cmd,
							t_env_vars **env_list);
void					ft_check_input_redirs(t_command **cmd,
							t_env_vars **env_list);
void					ft_check_redir_to_pipe(t_command **curr_cmd,
							int *fd_pipe);
int						ft_check_if_heredoc(t_command **cmd, char *path,
							char *full_path);

// CHARACTER CHECK
int						is_alphanumeric(char c);
int						ft_is_space(char c);
int						ft_is_redir_pipe(char c);
int						ft_is_quote(char c);
int						ft_is_a_valid_character(char c);
int						ft_is_redir_pipe(char c);

// QUOTES
char					*handle_quotes(char *input, t_env_vars **env_list);
void					ft_handle_quotes_alltokens(t_command **cmd,
							t_env_vars **env_list);
void					ft_handle_quotes_single_token(t_command **cmd,
							t_env_vars **env_list, int i);
void					extract_and_handle(int *j, char *input, int *i,
							t_env_vars **env_list);
// SIGNALS
void					signal_handler(int sig);
int						signal_no_input(int action, int code);
void					sigint_handler(int sig);
int						ft_sigint_checker(int action, int code);
void					ft_check_heredoc_signal(t_command **cmd,
							t_env_vars **env_list);

// FREE MEMORY
void					ft_free_env_list(t_env_vars **env_list);
void					ft_free_tokens(t_tokens *cmd_line, int total_tokens);
void					ft_free_all_commands(t_command **cmd);
void					ft_free_cmd(t_command **cmd);
void					ft_free_heredoc(t_command **cmd, char **dirs,
							t_env_vars **env_list, int signal);
void					ft_free_in_child_exec(t_command **curr_cmd,
							t_env_vars **env_list);

// HEREDOC
void					ft_heredoc(t_command **cmd, t_env_vars **env_list);
void					allocate_heredoc_output(char *input_line,
							t_env_vars **env_list);
void					allocate_heredoc_text(t_command **cmd);

// OTHER
void					handle_exit_code(t_env_vars **env_list, int *j,
							char *variabile);
char					*ft_get_cmdname(char *str);
char					*ft_get_path(t_env_vars **env_list);
void					*ft_realloc(void *ptr, size_t prev_size,
							size_t new_size);

#endif
