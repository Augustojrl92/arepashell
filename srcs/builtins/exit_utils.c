/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:24:02 by layala-s          #+#    #+#             */
/*   Updated: 2025/02/25 22:01:10 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(void	*data)
{
	t_token	*token;

	token = data;
	free(token->line);
	free(token->cmd);
	if (token->args)
		ft_free_sarray(token->args);
	if (token->outfiles)
		ft_free_sarray(token->outfiles);
	if (token->infiles)
		ft_free_sarray(token->infiles);
	if (token->heredoc)
		ft_free_sarray(token->heredoc);
	free(token);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_env(shell);
	free_tree(shell, shell->token_tree);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	do_exit(t_token *token)
{
	int	exit_code;

	if (token->args[1])
	{
		if (!is_numeric(token->args[1]))
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(token->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit_code = 255;
		}
		else if (token->args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			return (1);
		}
		else
			exit_code = ft_atoi(token->args[1]);
	}
	else
		exit_code = g_signal_data;
	if (getpid() == token->shell->main_pid)//agregue esto
        printf("exit\n");//agregue esto
	// free_shell(token->shell);
	// printf(" VALOR DESPUES %d\n", token->is_pipe);
	// if (token->is_pipe == 0)
	// 	printf("exit\n");
	exit(exit_code);
}
