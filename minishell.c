/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:41:19 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:41:21 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_wait_for_input(t_env_vars **env_list)
{
	char	*input;

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
			ft_lex(input, &first_env, envp);
			add_history(input);
			free(input);
		}
	}
	return (0);
}
