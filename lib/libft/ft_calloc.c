/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:11:41 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:07:17 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	register char	*new;
	register size_t	bytes;
	register size_t	x;

	bytes = count * size;
	new = (char *) malloc(bytes);
	if (NULL != new)
	{
		x = 0;
		while (x < bytes)
		{
			new[x] = '\0';
			x++;
		}
	}
	return ((void *) new);
}
