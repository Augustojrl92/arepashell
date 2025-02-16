/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:08:49 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:17:05 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	count;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	while (src[i] && (dest_len + i) < dstsize - 1 && dstsize != 0)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	if (i != 0)
		dst[dest_len + i] = '\0';
	if (dstsize < dest_len)
		count = dstsize + src_len;
	else
		count = dest_len + src_len;
	return (count);
}
