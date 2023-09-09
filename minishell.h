#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <errno.h>

typedef struct s_command
{
    int argc;
    char **argv;
    int is_builtin;
} t_command;


char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);


//BUILTINS
void ft_echo(t_command **cmd);
void ft_cd(t_command **cmd);
void ft_pwd(t_command **cmd);
void ft_export(t_command **cmd);
void ft_unset(t_command **cmd);
void ft_env(t_command **cmd);
void ft_exit(t_command **cmd);

//SHELL CORE
void ft_lex(char* input);
void ft_parse(char** cmd_line, int num_tokens);
void ft_execute(t_command **cmd);
