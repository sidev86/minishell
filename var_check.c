/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:30:46 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/09 14:30:47 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_validity(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && ((arg[i] >= '0' && arg[i] <= '9') || arg[i] == '='))
			return (1);
		if (!ft_is_a_valid_character(arg[i]))
			return (1);
		i++;
	}
	return (0);
}
