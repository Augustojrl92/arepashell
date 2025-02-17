/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:40:04 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 19:58:51 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_prefix(const char *filename, const char *prefix)
{
	size_t	p_len;

	p_len = ft_strlen(prefix);
	return (ft_strncmp(filename, prefix, p_len) == 0);
}

static int	check_suffix(const char *filename, const char *suffix)
{
	size_t	f_len;
	size_t	s_len;

	f_len = ft_strlen(filename);
	s_len = ft_strlen(suffix);
	if (f_len < s_len)
		return (0);
	return (ft_strcmp(filename + (f_len - s_len), suffix) == 0);
}

static int	match_pattern(const char *filename, const char *pattern)
{
	const char	*star;
	char		*prefix;
	char		*suffix;

	star = ft_strchr(pattern, '*');
	if (!star)
		return (ft_strcmp(filename, pattern) == 0);
	prefix = ft_substr(pattern, 0, star - pattern);
	suffix = ft_strdup(star + 1);
	if (!check_prefix(filename, prefix))
	{
		free(prefix);
		free(suffix);
		return (0);
	}
	if (!check_suffix(filename, suffix))
	{
		free(prefix);
		free(suffix);
		return (0);
	}
	free(prefix);
	free(suffix);
	return (1);
}

char	**expand_wildcard_pattern(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;

	matches = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(entry->d_name, pattern))
			matches = ft_add_to_sarray(matches, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}
