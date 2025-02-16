/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:10:16 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 20:32:59 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_dcount(long nb)
{
	size_t	dcount;

	dcount = 0;
	if (nb < 0)
	{
		dcount++;
		nb *= -1;
	}
	while (nb > 9)
	{
		nb /= 10;
		dcount++;
	}
	return (dcount);
}

char	*ft_itoa(int n)
{
	long			nb;
	unsigned int	dcount;
	char			*out;

	nb = (long)n;
	dcount = ft_dcount(nb);
	out = ft_calloc(dcount + 2, sizeof(char));
	if (!out)
		return (NULL);
	if (nb < 0)
	{
		out[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		out[0] = '0';
	while (nb > 0)
	{
		out[dcount] = ('0' + (nb % 10));
		nb /= 10;
		dcount--;
	}
	return (out);
}
