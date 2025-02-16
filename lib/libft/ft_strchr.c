/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:25:11 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:16:02 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	j;
	char	*strg;

	i = 0;
	j = (char) c;
	if (!str)
		return (NULL);
	strg = (char *) str;
	while (strg[i])
	{
		if (strg[i] == j)
			return (&strg[i]);
		i++;
	}
	if (strg[i] == j)
		return (&strg[i]);
	return (NULL);
}
