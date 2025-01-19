/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:33:54 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/03 17:14:11 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s1[j])
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}

char	*ft_strjoinfree(char *s1, char *s2, int which)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	if (!which || which == 2)
	{
		free(s1);
		s1 = NULL;
	}
	if (which)
	{
		free(s2);
		s2 = NULL;
	}
	return (joined);
}
