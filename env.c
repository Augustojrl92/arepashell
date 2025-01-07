/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:07:16 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/07 05:07:17 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	print_list(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	if (var->name && var->value)
		printf("%s=%s\n", var->name, var->value);
}

int	built_in_env(t_shell	*shell)
{
	ft_lstiter(shell->enviroment, print_list);
	return (EXIT_SUCCESS);
}
