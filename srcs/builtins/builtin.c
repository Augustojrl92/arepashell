/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:30:00 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 20:36:13 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_in_cd(t_shell *shell, t_token *token)
{
	char	buff[PATH_MAX + 1];
	char	*cwd;
	int		i;

	check_and_restore_directory(shell);
	cwd = getcwd(buff, PATH_MAX + 1);
	i = 0;
	if (!cwd)
	{
		check_dir(shell);
		cwd = getcwd(buff, PATH_MAX + 1);
	}
	while (token->args[i])
		i++;
	if (i > 2)
		return (printf("cd: too many arguments\n"), 1);
	if (token->args[1] == NULL)
		go_home(shell);
	else if (token->args[1][0] == '-' && token->args[1][1] == '\0')
		do_last_folder(shell, cwd);
	else
		go_folder(token, shell);
	return (0);
}

int	built_in_echo(t_token *token)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (token->args[i] && is_valid_n_flag(token->args[i]))
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

int	built_in_exit(t_shell *shell, t_token *token)
{
	(void)shell;
	do_exit(token);
	return (0);
}

int	built_in_pwd(t_shell *shell)
{
	char	buff[PATH_MAX + 1];
	char	*cwd;

	check_and_restore_directory(shell);
	cwd = getcwd(buff, PATH_MAX + 1);
	if (!cwd)
	{
		check_dir(shell);
		cwd = getcwd(buff, PATH_MAX + 1);
	}
	printf("%s\n", cwd);
	return (0);
}

int	built_in_unset(t_shell *shell, t_token *token)
{
	(void)shell;
	if (token->args[1] == NULL)
		printf("unset: not enough arguments\n");
	else
		do_unset(shell, token);
	return (0);
}
