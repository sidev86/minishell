#include "minishell.h"

int	check_var_validity(char *arg)
{
	int	i; 
	
	i = 0; 
	
	while(arg[i])
	{
		if (i == 0 && ((arg[i] >= '0' && arg[i] <= '9') || arg[i] == '='))
		{
			fprintf(stderr, " not a valid identifier\n");
			return 1;
		}	
		if (!ft_is_a_valid_character(arg[i]))
		{
			fprintf(stderr, " not a valid identifier\n");
			return 1;
		}
		i++;
	}
	return 0;
}
