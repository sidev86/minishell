#include "minishell.h"

static char	*ft_wait_for_input(t_env_vars **env_list)
{
	char	*input;
	//rl_redisplay();
	
	input = readline("minishell$ ");
	if (!input)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		ft_free_env_list(env_list);
		exit(0);
	}
	if (input[0] == '\0')
		return (NULL);
	return (input);
}

static int	ft_command_is_exit(char *input, t_env_vars **env_list)
{
	char	*str;
	int		cmd_len;
	int		i;

	cmd_len = 0;
	i = 0;
	while (input[i] != ' ' && input[i] != '\t' && input[i])
	{
		cmd_len++;
		i++;
	}
	str = ft_substr(input, 0, cmd_len);
	if (cmd_len == 4 && !ft_strcmp(str, "exit"))
	{
		ft_free_env_list(env_list);
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

static void	handle_exit_command(char *input, t_env_vars **env_list)
{
	if (ft_command_is_exit(input, env_list))
	{
		free(input);
		exit(44);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_env_vars	*first_env;

	first_env = 0;
	ft_create_env_list(&first_env, envp);
	if (argc > 1 || argv[1])
		return (1);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGINT, signal_handler);
		input = ft_wait_for_input(&first_env);
		if (input)
			input[ft_strlen(input)] = '\0';
		if (input != NULL)
		{
			handle_exit_command(input, &first_env);
			ft_lex(input, &first_env, envp);
			add_history(input);
			free(input);
		}
		
		
	}
	return (0);
}
