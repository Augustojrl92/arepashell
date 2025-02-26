/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:09:05 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/24 15:20:28 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_next_var(t_automata	*a)
{
	int		i;
	int		j;

	i = a->i + 1;
	j = 0;
	if (a->str[i] == '$')
		return (ft_strdup("$$"));
	if (a->str[i] == '?')
		return (ft_strdup("?"));
	if (!ft_isalpha(a->str[i]) && a->str[i] != '_' && a->str[i] != '?')
		return (ft_strdup("$"));
	while (a->str[i] != '\0' && ft_strchr(" \t\n.,:;@-+\"=#/(){}[]\"\'^*\\?$",
			a->str[i]) == NULL)
	{
		i++;
		j++;
	}
	return (ft_substr(a->str, a->i + 1, j));
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
	if (ft_samestr(var, "$$"))
		str = ft_itoa(getpid());
	else if (ft_samestr(var, "$"))
		str = ft_strdup("$");
	else
		str = find_value(token->shell->enviroment, var);
	if (str == NULL && ft_samestr("?", var))
	{
		if (g_signal_data != SIGINT)
			str = ft_itoa(token->shell->exit_status);
		else
			str = ft_itoa(130);
	}
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
