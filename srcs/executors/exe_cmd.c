/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:07:32 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/20 23:10:38 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_exit_status(char *cmd, int error_number)
{
	if (error_number == EACCES)
	{
		perror(cmd);
		return (ESCAPE_126);
	}
	if (error_number == ENOENT)
	{
		perror(cmd);
		return (ESCAPE_127);
	}
	return (0);
}

void	execute_multiple_paths(t_shell *shell, t_token *token, char **paths)
{
	char	*full_cmd;
	int		i;

	i = -1;
	full_cmd = NULL;
	while (paths[++i])
	{
		full_cmd = ft_strjoin(paths[i], token->cmd);
		if (!access(full_cmd, X_OK))
			execve(full_cmd, token->args, shell->default_env);
		free(full_cmd);
	}
}

void	exe_path_cmd(t_shell *shell, t_token *token)
{
	char	*path_var;
	char	**paths;

	errno = 0;
	path_var = find_value(shell->enviroment, "PATH");
	paths = get_path_var(shell);
	if (!ft_strchr(token->cmd, '/') && path_var)
	{
		free(path_var);
		execute_multiple_paths(shell, token, paths);
	}
	else
	{
		if (!access(token->cmd, X_OK))
		{
			if (execve(token->cmd, token->args, shell->default_env) == -1)
				exit(127);
		}
	}
	ft_free_sarray(paths);
	ft_free_sarray(shell->default_env);
	exit(set_exit_status(token->cmd, errno));
}
