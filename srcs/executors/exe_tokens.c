/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:07:42 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/25 21:54:27 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_and_restore_directory(t_shell *shell)
{
	char	buff[PATH_MAX + 1];

	if (getcwd(buff, PATH_MAX + 1) == NULL)
	{
		perror("Warning: Current directory removed");
		if (shell->last_path && chdir(shell->last_path) == 0)
		{
			if (getcwd(buff, PATH_MAX + 1) != NULL)
			{
				free(shell->last_path);
				shell->last_path = ft_strdup(buff);
			}
		}
		else
			go_home(shell);
	}
}

void	exe_cmd_or_built(t_shell	*shell, t_token	*token)
{
	if (is_built_in(token->cmd))
		exe_built_in(token, shell);
	else
		exe_path_cmd(shell, token);
}

void	wait_childs(t_token *token, int twice)
{
	if (twice)
		wait(&token->shell->exit_status);
	if (WIFEXITED(token->shell->exit_status))
		token->shell->exit_status = WEXITSTATUS(token->shell->exit_status);
	else if (WIFSIGNALED(token->shell->exit_status))
		token->shell->exit_status = 128 + WTERMSIG(token->shell->exit_status);
	if (token->shell->child)
		exit(token->shell->exit_status);
}

void	exe_minishell_recursive(t_tree	*node)
{
	t_token	*token;
	int		pid;
	int		fd[2];

	if (!node)
		exit(EXIT_SUCCESS);
	token = (t_token *)node->data;
	token->is_pipe = 0;
	//printf("VALOR AQUÍ %d\n", token->is_pipe);
	pid = 0;
	if (ft_samestr(token->line, PIPE_LINE))
	{
		if (pipe(fd) == -1)
			return ;
		token->is_pipe = 1;
		child_pipe_redir(node, token, pid, fd);
		wait_childs(token, TRUE);
	}
	else
		exe_comand_node(token, pid);
	return ;
}
