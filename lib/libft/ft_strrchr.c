/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:56:53 by jlara-na          #+#    #+#             */
/*   Updated: 2022/06/20 20:23:53 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*res;
	char	*strg;
	char	j;

	i = 0;
	j = (char) c;
	strg = (char *) str;
	res = NULL;
	while (strg[i])
	{
		if (strg[i] == j)
			res = &strg[i];
		i++;
	}
	if (strg[i] == j)
		res = &strg[i];
	return (res);
}
