#include "minishell.h"

int	is_a_valid_character(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||(c >= '0' && c <= '9') || (c == '_'));
}

int	check_var_validity(char *arg)
{
	int	i; 
	
	i = 0; 
	
	while(arg[i])
	{
		//printf("arg di i = %c\n", arg[i]);
		if (i == 0 && ((arg[i] >= '0' && arg[i] <= '9') || arg[i] == '='))
		{
			fprintf(stderr, " not a valid identifier\n");
			return 1;
		}	
		if (!is_a_valid_character(arg[i]))
		{
			fprintf(stderr, " not a valid identifier\n");
			return 1;
		}
		i++;
	}
	//printf("var valida\n");
	return 0;
}
