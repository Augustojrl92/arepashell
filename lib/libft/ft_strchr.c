/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:38:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/27 01:18:56 by jlara-na         ###   ########.fr       */
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
