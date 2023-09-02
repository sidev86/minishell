#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

void ft_echo(char** cmd);
void ft_cd();
void ft_pwd();
void ft_export();
void ft_unset();
void ft_env();
void ft_exit();