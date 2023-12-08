/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: extrimer <extrimer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:19:34 by sibrahim          #+#    #+#             */
/*   Updated: 2023/12/08 11:38:20 by extrimer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL)
		return (NULL);
	while (i < n)
	{
		*(char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}
