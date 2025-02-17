/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:26:49 by layala-s          #+#    #+#             */
/*   Updated: 2025/01/28 12:07:32 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_unset(t_shell *shell, t_token *token)
{
	t_list	*current;
	t_list	*prev;
	t_var	*var;

	current = shell->enviroment;
	prev = NULL;
	while (current)
	{
		var = (t_var *)current->content;
		if (var && var->name && ft_strcmp(var->name, token->args[1]) == 0)
		{
			free(var->name);
			free(var->value);
			free(var);
			if (prev)
				prev->next = current->next;
			else
				shell->enviroment = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
