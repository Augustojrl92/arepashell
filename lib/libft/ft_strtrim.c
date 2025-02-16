/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:47:46 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:18:37 by aurodrig         ###   ########.fr       */
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
