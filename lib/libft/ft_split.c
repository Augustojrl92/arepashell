/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:43:06 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:15:35 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(const char *str, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			wcount++;
		i++;
	}
	return (wcount);
}

static int	ft_wlen(const char *str, char c, int i)
{
	int	wlen;

	wlen = 0;
	while (str[i])
	{
		if (str[i] != c)
			wlen++;
		else
			break ;
		i++;
	}
	return (wlen);
}

static void	*ft_freemem(char **split, int wcount)
{
	int	i;

	i = 0;
	while (i < wcount)
		free(split[i++]);
	free(split[i]);
	return (NULL);
}

static char	**ft_fill(const char *s, char c, int wcount, char **split)
{
	int	i;
	int	j;
	int	k;
	int	wlen;

	i = 0;
	j = 0;
	while (i < wcount)
	{
		while (s[j] == c)
			j++;
		k = 0;
		wlen = ft_wlen(s, c, j);
		split[i] = (char *) malloc((wlen + 1) * sizeof(char));
		if (!split[i])
			return (ft_freemem(split, wcount));
		while (k < wlen)
			split[i][k++] = s[j++];
		split[i][k] = '\0';
		i++;
	}
	split [i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		wcount;
	char	**split;

	if (!s)
		return (NULL);
	wcount = ft_wcount(s, c);
	split = (char **) malloc((wcount + 1) * (sizeof (char *)));
	if (!split)
		return (NULL);
	return (ft_fill(s, c, wcount, split));
}
