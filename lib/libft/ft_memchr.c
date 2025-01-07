/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:24:54 by jlara-na          #+#    #+#             */
/*   Updated: 2022/06/30 15:08:52 by jlara-na         ###   ########.fr       */
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
