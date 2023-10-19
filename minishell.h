#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <errno.h>

typedef struct s_command
{
    int argc;
    char **argv;
    char **envp;
    int is_builtin;
} t_command;

typedef struct s_env_vars
{
    char *env_str;
    char *var;
    char *value;
    struct s_env_vars *next;
} t_env_vars;


char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);



//BUILTINS
void ft_echo(t_command **cmd);
void ft_cd(t_command **cmd);
void ft_pwd();
void ft_export(t_command **cmd, t_env_vars ***env_list);
void ft_unset(t_command **cmd, t_env_vars ***env_list);
void ft_env(t_command **cmd, t_env_vars ***env_list);
void ft_exit(t_command **cmd);

//SHELL CORE
void ft_lex(char* input, t_env_vars **env_list, char **envp);
void ft_parse(char** cmd_line, int num_tokens, t_env_vars **env_list, char **envp);
void ft_execute(t_command **cmd, t_env_vars **env_list, char **envp);

void ft_create_env_list(t_env_vars **first, char **envp);
void ft_print_env_list(t_env_vars **first);
int ft_env_var_exists(t_env_vars ***env_list, char *var);
void ft_set_env_var(t_env_vars ***env_list, char *env_str, int var_len);
void ft_update_env_var(t_env_vars ***env_list, char *env_str, int var_len);
void ft_remove_env_var(t_env_vars ***env_list, char *env_str, int var_len);

