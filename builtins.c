#include "minishell.h"

int ft_echo(t_command **cmd) //t_command cmd
{
	int i = 1;
	int no_newline = 0;

	if (i < (*cmd)->argc && strcmp((*cmd)->argv[i], "-n") == 0)
	{
		no_newline = 1;
		i++; // Se l'opzione -n è presente, passa al prossimo argomento
	}
	while (i < (*cmd)->argc)
	{
		if ((*cmd)->argv[i])
		{
			printf("%s", (*cmd)->argv[i]);
			if (i < (*cmd)->argc - 1)
				printf(" ");
		}
		i++;
	}
	if (i < (*cmd)->argc || no_newline == 0) 
		printf("\n"); // Aggiungi una nuova linea se l'opzione -n non è presente o se ci sono più argomenti
	return (0);
}

int ft_cd(t_command **cmd)
{
	if ((*cmd)->argc == 1 || (strcmp((*cmd)->argv[1], "~") == 0))
	{
		// Nessun argomento, torna alla home directory
		char *home_directory = getenv("HOME");
		
		if (home_directory == NULL)
		{
			printf("La variabile HOME non è impostata.\n");
			return (130);
		}

		if (chdir(home_directory) == -1)
		{
			perror("chdir");
			return (1);
		}
	}
	else if ((*cmd)->argc == 2)
	{
		char *new_directory = (*cmd)->argv[1];

		if (chdir(new_directory) == -1)
		{
			perror("chdir");
			return (1);
		}
	}
	else
	{
		fprintf(stderr, " too many arguments"); 
		return (1);
	}
	return (0);
}

int ft_pwd()
{
	char *current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("getcwd");
		return (130);
	}

	printf("%s\n", current_dir);
	free(current_dir);
	return (0);
}

int ft_export(t_command **cmd, t_env_vars ***env_list)
{
	char *env_arg;
	char *var_name;
	int var_len;
	
	env_arg = (*cmd)->argv[1];
	//printf("env arg= %s\n", env_arg);
	if (!env_arg)
		return 1;
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
		return (1);	
	
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
	return (0);
}

int ft_unset(t_command **cmd, t_env_vars ***env_list)
{
	char *env_arg;
	int var_len;
	//t_env_vars *curr;
	env_arg = (*cmd)->argv[1];
	if (!env_arg)
		return (0);
	var_len = ft_strlen(env_arg);
	if (ft_env_var_exists(env_list, ft_substr(env_arg, 0, var_len)) && env_arg != NULL)
	{
		//printf("variabile trovata\n");
		ft_remove_env_var(env_list, env_arg, var_len);
	}
	return (0);     
}

int ft_env(t_env_vars ***env_list)
{
	t_env_vars *curr; 

	curr = **env_list; 
	while (curr != NULL)
	{
		printf("%s\n", curr->env_str);
		curr = curr->next; 
	}
	return (0);
}

/*void ft_exit(t_command **cmd)
{
    printf("exit\n");
    exit(0);
}*/
