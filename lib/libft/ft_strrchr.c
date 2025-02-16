/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:47:46 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:18:29 by aurodrig         ###   ########.fr       */
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
