#include "minishell.h"

char	*ft_wait_for_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		exit(0);
	}
	if (input[0] == '\0')
		return (NULL);
	return (input);
}

int	ft_command_is_exit(char *input)
{
	int	cmd_len;
	int	i;

	cmd_len = 0;
	i = 0;
	while (input[i] != ' ' && input[i] != '\t' && input[i])
	{
		cmd_len++;
		i++;
	}
	if (cmd_len == 4 && !strcmp(ft_substr(input, 0, cmd_len), "exit"))
		return (10);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_env_vars	*first_env;

	first_env = 0;
	ft_create_env_list(&first_env, envp);
	setenv("TERM", "xterm", 1);
	if (argc > 1 || argv[1])
		return (1);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGINT, signal_handler);
		input = ft_wait_for_input();
		if (input)
			input[ft_strlen(input)] = '\0';
		if (input != NULL)
		{
			if (ft_command_is_exit(input))
			{
				free(input);
				return (1);
			}
			ft_lex(input, &first_env, envp);
			add_history(input);
			free(input);
		}
	}
	return (0);
}
