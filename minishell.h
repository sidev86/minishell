#ifndef MINISHELL_H
# define MINISHELL_H



# define GET_CODE 0
# define SET_CODE 1
# define PRINT 2

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
//#include <errno.h>


typedef struct s_tokens
{
	char	*token;
	int	is_symbol;
	int	in_quotes;
}		t_tokens;


typedef struct s_command
{
    int argc;
    char **argv;
    char **envp;
    char **heredoc_text;
    char **end_tokens;
    int skip_terminator;
    int has_heredoc;
    int heredoc_counter;
    int is_builtin;
    int fd_terminal;
    int fd_stdinput;
    int num_redirs;
    int num_tokens;
    int number;
    int num_cmds;
    int redir_out;
    int redir_in;
    struct s_command *next;
    struct s_command *prev;
} t_command;

typedef struct s_env_vars
{
    char *env_str;
    char *var;
    char *value;
    struct s_env_vars *next;
} t_env_vars;

//STRING FUNCTIONS
int 	ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, char *src);

//BUILTINS
void ft_echo(t_command **cmd);
void ft_cd(t_command **cmd);
void ft_pwd();
void ft_export(t_command **cmd, t_env_vars ***env_list);
void ft_unset(t_command **cmd, t_env_vars ***env_list);
void ft_env(t_env_vars ***env_list);
void ft_exit(t_command **cmd);

//SHELL CORE
void ft_lex(char* input, t_env_vars **env_list, char **envp);
void ft_parse(t_tokens* cmd_line, int num_tokens, t_env_vars **env_list, char **envp);
void ft_execute(t_command **cmd, t_env_vars **env_list, char **envp);


//ENV LIST
void ft_create_env_list(t_env_vars **first, char **envp);
void ft_print_env_list(t_env_vars **first);
int ft_env_var_exists(t_env_vars ***env_list, char *var);
void ft_set_env_var(t_env_vars ***env_list, char *env_str, int var_len);
void ft_update_env_var(t_env_vars ***env_list, char *env_str, int var_len);
void ft_remove_env_var(t_env_vars ***env_list, char *env_str, int var_len);

//ERRORS
int	errors_manager(int action, int code, char *msg, char *arg);

char	*ft_itoa(int n);
char	*handle_quotes(char *input);
int	check_var_validity(char *arg);
void ft_check_output_redirs(t_command **cmd);
void ft_check_input_redirs(t_command **cmd);
int ft_is_redir_pipe(char c);
void	signal_handler(int sig);
void	ft_heredoc(t_command **cmd);

void	extract_and_handle(char *output, int *j, char *input, int *i);

int	is_alphanumeric(char c);
int ft_is_space(char c);
int ft_is_redir_pipe(char c);
int ft_is_quote(char c);
int	ft_count_tokens(char* input);

#endif

