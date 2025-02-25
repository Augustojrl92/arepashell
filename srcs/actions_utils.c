/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:06:43 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/24 14:40:09 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_len(char	*str, char type)
{
	int	i;

	i = 1;
	while (str[i] != type && str[i] != '\0')
		i++;
	return (i);
}

int	arg_length(char	*arg)
{
	int	len;

	len = 0;
	while (arg[len] == ' ' || arg[len] == '\t')
		len++;
	while (arg[len] != '\0' && arg[len] != '<' && arg[len] != '>')
	{
		if (arg[len] == '\'' || arg[len] == '\"')
			len += quote_len(arg + len, arg[len]);
		if ((arg[len] == ' ' || arg[len] == '\t'
				|| arg[len] == '\n'))
			break ;
		len++;
		if (len >= (int)ft_strlen(arg))
			break ;
	}
	return (len);
}

char	*get_next_word(t_automata *a, int remove_quotes)
{
	char	*substr;
	char	*trim;
	char	*final;
	int		i;

	i = arg_length(a->str + a->i);
	substr = ft_substr(a->str, a->i, i);
	trim = ft_strtrim(substr, " \t\n");
	free(substr);
	a->j = a->i;
	if (remove_quotes && trim && ft_strlen(trim) >= 2)
	{
		if ((trim[0] == '\'' && trim[ft_strlen(trim) - 1] == '\'')
			|| (trim[0] == '\"' && trim[ft_strlen(trim) - 1] == '\"'))
		{
			final = ft_substr(trim, 1, ft_strlen(trim) - 2);
			free(trim);
			return (final);
		}
	}
	return (trim);
}
