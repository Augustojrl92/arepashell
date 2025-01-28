/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:08:26 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/22 10:39:02 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_new_var(t_list	*enviroment, t_var	*newvar)
{
	t_list	*node;
	t_var	*var;

	node = NULL;
	var = NULL;
	node = ft_lstfind(enviroment, find_var, newvar->name);
	if (node)
	{
		var = (t_var *)(node->content);
		free(var->value);
		var->value = newvar->value;
		free(newvar->name);
		free(newvar);
		newvar = NULL;
	}
	else
		ft_lstadd_back(&enviroment, ft_lstnew(newvar));
}

int	is_valid_var_name(char	*arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (i == 0)
		{
			if (arg[i] != '_' && !ft_isalpha(arg[i]))
				return (0);
		}
		else
		{
			if (arg[i] != '_' && !ft_isalnum(arg[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

void	print_export(void	*content)
{
	t_var	*var;

	var = (t_var *)content;
	if (var->name && var->value)
		printf("declare -x %s=%s\n", var->name, var->value);
}

int	built_in_export(t_shell *shell, t_token	*token)
{
	t_var	*newvar;
	char	*value;
	int		i;
	int		j;

	newvar = NULL;
	value = NULL;
	i = 0;
	j = 0;
	if (!token->args[1])
		ft_lstiter(shell->enviroment, print_export);
	while (token->args[++i])
	{
		if (!is_valid_var_name(token->args[i]))
			return (EXIT_FAILURE);
		j = ft_chrpos(token->args[i], '=');
		if (j != -1)
			value = ft_substr(token->args[i], j + 1, INT_MAX);
		else
			value = ft_calloc(sizeof(char *), 1);
		newvar = create_var(ft_substr(token->args[i], 0, j), value);
		add_new_var(shell->enviroment, newvar);
	}
	return (EXIT_SUCCESS);
}
