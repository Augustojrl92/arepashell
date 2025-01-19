/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:07:50 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/13 18:27:10 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	stdout_redirection(t_token	*token)
{
	int	i;

	i = -1;
	token->last_outf_fd = -1;
	if (token->outfiles)
	{
		while (token->outfiles[++i])
		{
			if (token->append)
				token->last_outf_fd = open(token->outfiles[i],
						O_CREAT | O_APPEND | O_WRONLY, 0644);
			else
				token->last_outf_fd = open(token->outfiles[i],
						O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (token->outfiles[i + 1])
				close(token->last_outf_fd);
		}
	}
	if (token->last_outf_fd != -1)
		dup2(token->last_outf_fd, STDOUT_FILENO);
	return ;
}

void	stdin_stdout_reset(t_token	*token, int saved_std[2])
{
	if (dup2(saved_std[0], STDIN_FILENO) == -1)
	{
		perror("dup2 stdin");
		close(token->last_outf_fd);
		close(token->last_inf_fd);
		close(saved_std[0]);
		close(saved_std[1]);
		return ;
	}
	if (dup2(saved_std[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 stdout");
		close(token->last_outf_fd);
		close(token->last_inf_fd);
		close(saved_std[0]);
		close(saved_std[1]);
		return ;
	}
	close(token->last_outf_fd);
	close(token->last_inf_fd);
	close(saved_std[0]);
	close(saved_std[1]);
}

void	child_pipe_redir(t_tree *node, t_token *token, int pid, int fd[2])
{
	pid = fork();
	if (!pid)
	{
		//set_sig_handler(SIG_DFL, 1);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[READ_END]);
		token->shell->child = 1;
		exe_minishell_recursive(node->left);
	}
	else
	{
		pid = fork();
		if (!pid)
		{
			//set_sig_handler(SIG_DFL, 1);
			dup2(fd[READ_END], STDIN_FILENO);
			close(fd[WRITE_END]);
			token->shell->child = 1;
			exe_minishell_recursive(node->right);
		}
	}
	close(fd[WRITE_END]);
	close(fd[READ_END]);
}

void	exe_comand_node(t_token	*token, int pid)
{
	if (!token->shell->child)
	{
		if (is_built_in(token->cmd))
		{
			exe_built_in_with_redirs(token->shell, token);
		}
		else
		{
			pid = fork();
			if (!pid)
			{
				//set_sig_handler(SIG_DFL, 1);
				stdin_redirection(token);
				stdout_redirection(token);
				exe_path_cmd(token->shell, token);
			}
			wait_childs(token, FALSE);
		}
	}
	else
	{
		stdin_redirection(token);
		stdout_redirection(token);
		exe_cmd_or_built(token->shell, token);
	}
}
