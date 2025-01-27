/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:26:49 by layala-s          #+#    #+#             */
/*   Updated: 2025/01/27 12:26:50 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void get_env(t_shell *shell, t_token *token)
{
    t_list  *current = shell->enviroment;
    t_var   *var;

    while (current)
    {
        var = (t_var *)current->content;
        if (var && var->name && strcmp(var->name, token->args[1]) == 0)
        {
            printf("%s=%s\n", var->name, var->value);
            free(token->args[1]);
            return ;
        }
        current = current->next;
    }
}
