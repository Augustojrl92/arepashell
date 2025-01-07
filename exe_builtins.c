/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:07:24 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/07 05:07:25 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	is_built_in(char	*cmd)
{
	if (ft_samestr(cmd, CD_BUILT))
		return (1);
	if (ft_samestr(cmd, ECHO_BUILT))
		return (1);
	if (ft_samestr(cmd, ENV_BUILT))
		return (1);
	if (ft_samestr(cmd, EXIT_BUILT))
		return (1);
	if (ft_samestr(cmd, EXPORT_BUILT))
		return (1);
	if (ft_samestr(cmd, PWD_BUILT))
		return (1);
	if (ft_samestr(cmd, UNSET_BUILT))
		return (1);
	return (0);
}

int	exe_built_in(void	*data, void	*context)
{
	t_token	*token;
	t_shell	*shell;

	token = (t_token *)data;
	shell = (t_shell *)context;
	if (ft_samestr(token->cmd, CD_BUILT))
		return (shell->exit_status = built_in_cd(shell, token));
	if (ft_samestr(token->cmd, ECHO_BUILT))
		return (shell->exit_status = built_in_echo(token));
	if (ft_samestr(token->cmd, ENV_BUILT))
		return (shell->exit_status = built_in_env(shell));
	if (ft_samestr(token->cmd, EXIT_BUILT))
		return (shell->exit_status = built_in_exit(shell, token));
	if (ft_samestr(token->cmd, EXPORT_BUILT))
		return (shell->exit_status = built_in_export(shell, token));
	if (ft_samestr(token->cmd, PWD_BUILT))
		return (shell->exit_status = built_in_pwd(shell));
	if (ft_samestr(token->cmd, UNSET_BUILT))
		return (shell->exit_status = built_in_unset(shell, token));
	return (shell->exit_status = 1);
}

//  int	dup_stdin(void)
// {
// 	int	saved_stdin;

// 	saved_stdin = dup(STDIN_FILENO);
// 	if (saved_stdin == -1)
// 	{
// 		perror("dup stdin");
// 		return (-1);
// 	}
// 	return (saved_stdin);
// }

// int	dup_stdout(void)
// {
// 	int	saved_stdout;

// 	saved_stdout = dup(STDOUT_FILENO);
// 	if (saved_stdout == -1)
// 	{
// 		perror("dup stdout");
// 		return (-1);
// 	}
// 	return (saved_stdout);
// }

void	exe_built_in_with_redirs(t_shell	*shell, t_token	*token)
{
	// int	saved_std[2];

	// saved_std[0] = dup_stdin();
	// saved_std[1] = dup_stdout();
	// stdin_redirection(token);
	// stdout_redirection(token);
	exe_built_in(token, shell);
	//stdin_stdout_reset(token, saved_std);
} 
