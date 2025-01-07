/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:30:00 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/07 00:50:29 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int built_in_cd(t_shell *shell, t_token *token)
{
    (void)shell;
    (void)token;
    printf("Builtin: cd\n");
    return (0);
}

int built_in_echo(t_token *token)
{
    (void)token;
    printf("Builtin: echo\n");
    return (0);
}

int built_in_env(t_shell *shell)
{
    (void)shell;
    printf("Builtin: env\n");
    return (0);
}

int built_in_exit(t_shell *shell, t_token *token)
{
    (void)shell;
    (void)token;
    printf("Builtin: exit\n");
    return (0);
}

int built_in_export(t_shell *shell, t_token *token)
{
    (void)shell;
    (void)token;
    printf("Builtin: export\n");
    return (0);
}

int built_in_pwd(t_shell *shell)
{
    (void)shell;
    printf("Builtin: pwd\n");
    return (0);
}

int built_in_unset(t_shell *shell, t_token *token)
{
    (void)shell;
    (void)token;
    printf("Builtin: unset\n");
    return (0);
}
