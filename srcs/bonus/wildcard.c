/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/16 20:07:13 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	**ft_remove_index_sarray(char **arr, int index)
{
	int	len;

	len = 0;
	if (!arr)
		return (NULL);
	while (arr[len])
		len++;
	if (index < 0 || index >= len)
		return (arr);
	free(arr[index]);
	while (index < len - 1)
	{
		arr[index] = arr[index + 1];
		index++;
	}
	arr[index] = NULL;
	return (arr);
}

void	expand_wildcards_in_args(t_token *token)
{
	int		i;
	char	**matches;

	i = 0;
	if (!token->args)
		return ;
	while (token->args[i])
	{
		if (!ft_strchr(token->args[i], '*'))
		{
			i++;
			continue ;
		}
		matches = expand_wildcard_pattern(token->args[i]);
		if (!matches || !matches[0])
		{
			ft_free_sarray(matches);
			i++;
			continue ;
		}
		token->args = ft_remove_index_sarray(token->args, i);
		token->args = ft_insert_sarray(token->args, matches, i);
		ft_free_sarray(matches);
	}
}

void	expand_wildcards_in_outfiles(t_token *token)
{
	int		i;
	char	**matches;

	i = 0;
	if (!token->outfiles)
		return ;
	while (token->outfiles[i])
	{
		if (!ft_strchr(token->outfiles[i], '*'))
		{
			i++;
			continue ;
		}
		matches = expand_wildcard_pattern(token->outfiles[i]);
		if (!matches || !matches[0])
		{
			ft_free_sarray(matches);
			i++;
			continue ;
		}
		token->outfiles = ft_remove_index_sarray(token->outfiles, i);
		token->outfiles = ft_insert_sarray(token->outfiles, matches, i);
		ft_free_sarray(matches);
	}
}
