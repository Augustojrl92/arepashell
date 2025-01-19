/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:00:26 by jlara-na          #+#    #+#             */
/*   Updated: 2022/07/17 22:29:21 by jlara-na         ###   ########.fr       */
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
