/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:43:41 by sibrahim          #+#    #+#             */
/*   Updated: 2024/01/24 14:43:42 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	void	*new;
	size_t	size;

	if (!ptr)
		return (NULL);
	new = malloc(new_size);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	if (prev_size < new_size)
		size = prev_size;
	else
		size = new_size;
	ft_memcpy(new, ptr, size);
	free(ptr);
	return (new);
}
