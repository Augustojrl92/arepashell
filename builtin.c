/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:30:00 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/22 10:29:22 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int built_in_cd(t_shell *shell, t_token *token)
{
    (void)shell;
    (void)token;
    printf("Builtin: cd\n");
    return (0);
}

int	built_in_echo(t_token	*token)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (token->args[i] && ft_samestr(token->args[i], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (token->args[i])
	{
		ft_putstr_fd(token->args[i++], 1);
		if (token->args[i])
			ft_putstr_fd(" ", 1);
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}



int built_in_exit(t_shell *shell, t_token *token)
{
    (void)shell;
    (void)token;
    printf("Builtin: exit\n");
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
