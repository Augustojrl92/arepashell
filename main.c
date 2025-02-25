/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:08:10 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/25 22:00:12 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_signal_data = 0;

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

void	main_loop(t_shell	*shell)
{
	while (1)
	{
		if (split_in_token_lines(shell))
		{
			ft_tree_in_order_arg(shell->token_tree, tokenize_node, shell);
			ft_tree_in_order_arg(shell->token_tree, expand_token, shell);
			if (shell->token_tree)
			{
				exe_minishell_recursive(shell->token_tree);
				wait_childs(shell->token_tree->data, TRUE);
			}
			ft_tree_in_order_arg(shell->token_tree, unlink_heredocs, shell);
		}
		ft_free_sarray(shell->path_var);
		free_tree(shell, shell->token_tree);
		free(shell->splitter.str);
	}
}

int	ft_sarrsize(char **arr)
{
	int	size;

	if (!arr)
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}

char	**duparr(char **argenv)
{
	char	**arr;
	int		i;

	i = -1;
	if (!argenv || !*argenv)
		return (NULL);
	arr = malloc(sizeof(char *) * (ft_sarrsize(argenv) + 1));
	while (argenv[++i])
		arr[i] = ft_strdup(argenv[i]);
	arr[i] = NULL;
	return (arr);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	shell.main_pid = getpid(); //agregue esto
	(void)ac;
	(void)av;
	do_signal();
	ft_bzero(&shell, sizeof(t_shell));
	import_env(&shell, envp);
	shell.default_env = duparr(envp);
	main_loop(&shell);
	free_env(&shell);
	return (EXIT_SUCCESS);
}
