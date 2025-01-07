/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:32:43 by jlara-na          #+#    #+#             */
/*   Updated: 2022/06/20 22:38:37 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[0])
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && needle[j] && (i + j) < len)
		{
			if (needle[j] != haystack[i + j])
				break ;
			j++;
		}
		if (!needle[j])
			return ((char *) &haystack[i]);
		i++;
	}
	return (NULL);
}
