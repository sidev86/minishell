#include "minishell.h"

int	is_a_valid_character(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_') || c == '=');
}

int	var_not_valid(char *arg)
{
	int	i; 
	
	i = 0; 
	while(arg[i])
	{
		if(i == 0 && arg[i] >= '0' && arg[i] <= '9')
		{
			perror(" not a valid identifier\n");
			return 1;
		}
			
		if(!is_a_valid_character(arg[i]))
		{
			perror(" not a valid identifier\n");
			return 1;
		}
		i++;
	}
	return 0;
}
