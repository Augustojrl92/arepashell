/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:09:05 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/22 10:32:28 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_next_var(t_automata	*a)
{
	char	*next_var;
	int		i;
	int		j;

	i = a->i + 1;
	j = 0;
	while (a->str[i] != '\0' && a->str[i] != ' ' && a->str[i] != '\t'
		&& a->str[i] != '\n' && a->str[i] != '$' && a->str[i] != '\''
		&& a->str[i] != '\"')
	{
		i++;
		j++;
	}
	next_var = ft_substr(a->str, a->i + 1, j);
	return (next_var);
}

void	insert_var(t_automata *a, void *data)
{
	t_token		*token;
	char		*str;
	char		*var;
	char		**pointer;

	token = (t_token *)data;
	pointer = (char **)token->data;
	var = get_next_var(a);
	str = find_value(token->shell->enviroment, var);
	if (str == NULL && ft_samestr("?", var))
		str = ft_itoa(token->shell->exit_status);
	free(var);
	*pointer = ft_strjoinfree(*pointer, str, 2);
}

void	insert_chr(t_automata *a, void *data)
{
	t_token		*token;
	char		str[2];
	char		**pointer;

	token = (t_token *)data;
	pointer = (char **)token->data;
	str[0] = a->str[a->i];
	str[1] = '\0';
	*pointer = ft_strjoinfree(*pointer, str, 0);
}
