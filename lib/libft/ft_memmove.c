/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 02:42:38 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:13:56 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dstbfr;
	char	*srcbfr;
	size_t	i;

	i = 0;
	dstbfr = (char *) dest;
	srcbfr = (char *) src;
	if (dstbfr > srcbfr)
		while (n-- > 0)
			dstbfr[n] = srcbfr[n];
	else
	{
		while (i < n && srcbfr != dstbfr)
		{
			dstbfr[i] = srcbfr[i];
			i++;
		}
	}
	return (dstbfr);
}
