/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 02:42:38 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:13:33 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		j;
	unsigned char		*str;

	i = 0;
	j = (unsigned char) c;
	str = (unsigned char *) s;
	while (i < n)
	{
		if (str[i] == j)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
