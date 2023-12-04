#include "minishell.h"

void ft_echo(t_command **cmd) //t_command cmd
{
	int i = 1;
	int no_newline = 0;
	
	if ((*cmd)->argv[i])
	{
		if (i < (*cmd)->argc && ft_strcmp((*cmd)->argv[i], "-n") == 0)
		{
			no_newline = 1;
			i++; // Se l'opzione -n è presente, passa al prossimo argomento
		}
	}
	//printf("argc = %d, num_tokens = %d\n", (*cmd)->argc, (*cmd)->num_tokens);
	while (i < (*cmd)->argc)
	{
		if ((*cmd)->argv[i])
		{
			printf("%s", (*cmd)->argv[i]);
			if (i < (*cmd)->argc - 1 && (*cmd)->argv[i+1])
				printf(" ");
		}
		i++;
	}
	if (i < (*cmd)->argc || no_newline == 0) 
		printf("\n"); // Aggiungi una nuova linea se l'opzione -n non è presente o se ci sono più argomenti
	errors_manager(SET_CODE, 0, NULL, NULL);
}

void ft_cd(t_command **cmd)
{
	if ((*cmd)->argc == 1 || (ft_strcmp((*cmd)->argv[1], "~") == 0))
	{
		// Nessun argomento, torna alla home directory
		char *home_directory = getenv("HOME");
		
		if (home_directory == NULL)
		{
			errors_manager(SET_CODE, 1, NULL, NULL);
			errors_manager(PRINT, 1, "Variable HOME not set\n", "Error");
			return ;
		}

		if (chdir(home_directory) == -1)
		{
			errors_manager(SET_CODE, 1, NULL, NULL);
			errors_manager(PRINT, 1, "No such file or directory\n", home_directory);
			return ;
		}
	}
	else if ((*cmd)->argc == 2)
	{
		char *new_directory = (*cmd)->argv[1];

		if (chdir(new_directory) == -1)
		{
			errors_manager(SET_CODE, 1, NULL, NULL);
			errors_manager(PRINT, 1, "No such file or directory\n", new_directory);
			return ;
		}
	}
	else
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Too many arguments", "Error");
		return ;
	}
	errors_manager(SET_CODE, 0, NULL, NULL);
}

void ft_pwd()
{
	char *current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		errors_manager(SET_CODE, 130, NULL, NULL);
		return ;
	}

	printf("%s\n", current_dir);
	
	errors_manager(SET_CODE, 0, NULL, NULL);
	free(current_dir);
	return ;
}

void ft_export(t_command **cmd, t_env_vars ***env_list)
{
	char *env_arg;
	char *var_name;
	int var_len;
	
	env_arg = (*cmd)->argv[1];
	//printf("env arg= %s\n", env_arg);
	if (!env_arg)
	{
		errors_manager(SET_CODE, 0, NULL, NULL);
		return ;
	}
	if (!ft_strchr(env_arg, '='))
		var_len = ft_strlen(env_arg);
	else
		var_len = (ft_strlen(env_arg) - ft_strlen(ft_strchr(env_arg,'=')));
		
	if (var_len == 0)
		var_len = 1;
	//printf("lunghezza nome var = %d\n",var_len);
	var_name = ft_substr(env_arg, 0, var_len);
	//printf("lunghezza nome var = %d\n",var_len);
	//printf("var name = %s\n", var_name);
	//printf("export env list = %s\n", (**env_list)->env_str);
	//printf("env arg = %s\n", env_arg);
	if (check_var_validity(var_name))
	{
		errors_manager(SET_CODE, 1, NULL, NULL);
		errors_manager(PRINT, 1, "Not a valid identifier", var_name);
		return ;
	}	
	
	if(!ft_env_var_exists(env_list, ft_substr(env_arg, 0, var_len)) && env_arg != NULL)
	{
		//printf("env var non esistente\n");
		ft_set_env_var(env_list, env_arg, var_len);
	}
	    
	else if (ft_env_var_exists(env_list, ft_substr(env_arg, 0, var_len)) && env_arg != NULL)
	{
		//printf("env var già esistente\n");
		ft_update_env_var(env_list, env_arg, var_len);
	}
	/*if(env_arg)
	{
		while(curr->next)
		    curr = curr->next; 
		curr->next = malloc(sizeof(t_env_vars));
		curr = curr->next; 
		curr->env_str = env_arg;

		//printf("var len = %d\n", var_len);

		curr->var = ft_substr(env_arg, 0, var_len);
		//curr->var = ft_strjoin(curr->var, "\0");
		printf("curr var = %s\n", curr->var); 
		curr->next = NULL;
	}   */
	errors_manager(SET_CODE, 0, NULL, NULL);
	return ;
}

void ft_unset(t_command **cmd, t_env_vars ***env_list)
{
	char *env_arg;
	int var_len;
	//t_env_vars *curr;
	env_arg = (*cmd)->argv[1];
	if (!env_arg)
	{
		errors_manager(SET_CODE, 0, NULL, NULL);
		return ;
	}
	var_len = ft_strlen(env_arg);
	if (ft_env_var_exists(env_list, ft_substr(env_arg, 0, var_len)) && env_arg != NULL)
	{
		//printf("variabile trovata\n");
		ft_remove_env_var(env_list, env_arg, var_len);
	}
	errors_manager(SET_CODE, 0, NULL, NULL);
	return ;     
}

void ft_env(t_env_vars ***env_list)
{
	t_env_vars *curr; 

	curr = **env_list; 
	while (curr != NULL)
	{
		printf("%s\n", curr->env_str);
		curr = curr->next; 
	}
	errors_manager(SET_CODE, 0, NULL, NULL);
	return ;
}

/*void ft_exit(t_command **cmd)
{
    printf("exit\n");
    exit(0);
}*/
