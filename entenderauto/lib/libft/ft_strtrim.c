/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:58:32 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/01 20:56:59 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	if_exist(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && if_exist(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (start < end && if_exist(set, s1[end - 1]))
		end--;
	str = (char *) ft_calloc(end - start + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (end > start)
	{
		end--;
		str[end - start] = s1[end];
	}
	return (str);
}
