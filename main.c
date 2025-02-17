/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:08:10 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/22 10:46:17 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_signal_data = 0;

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

void	free_tree(t_shell	*shell, t_tree	*tree)
{
	if (tree != NULL)
	{
		free_tree(shell, tree->left);
		free_token(tree->data);
		free_tree(shell, tree->right);
		free(tree);
		shell->token_tree = NULL;
	}
}

// Bucle principal
void	main_loop(t_shell	*shell)
{
	while (1)
	{
		if (split_in_token_lines(shell))
		{
			ft_tree_in_order_arg(shell->token_tree, tokenize_node, shell);
			// ft_tree_in_order_arg(shell->token_tree, expand_token, shell); <------ AQUI ESTÁ
			if (shell->token_tree)
				exe_minishell_recursive(shell->token_tree);
			ft_tree_in_order_arg(shell->token_tree, unlink_heredocs, shell);
		}
		ft_free_sarray(shell->default_env);
		ft_free_sarray(shell->path_var);
		free_tree(shell, shell->token_tree);
		free(shell->splitter.str);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	do_signal();
	ft_bzero(&shell, sizeof(t_shell));
	import_env(&shell, envp);
	main_loop(&shell);
	return (EXIT_SUCCESS);
}
