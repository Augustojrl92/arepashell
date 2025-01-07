/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:08:10 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/07 05:08:11 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

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

//Imprimir el árbol sintáctico (para depuración)
void	print_tree(t_tree *node, int depth)
{
	if (!node)
		return;
	for (int i = 0; i < depth; i++)
		printf("  ");
	t_token *token = (t_token *)node->data;
	if (token && token->line)
		printf("- Token: '%s'\n", token->line);
	else
		printf("- Nodo vacío.\n");
	print_tree(node->left, depth + 1);
	print_tree(node->right, depth + 1);
}

// Bucle principal
void	main_loop(t_shell	*shell)
{
	while (1)
	{
		if (split_in_token_lines(shell))
		{
			// Procesar tokens en el árbol sintáctico
			ft_tree_in_order_arg(shell->token_tree, tokenize_node, shell);

			//Mostrar el árbol sintáctico
			printf("\n>> Árbol sintáctico generado:\n");
			print_tree(shell->token_tree, 0);

			//Ejecutar comandos
			if (shell->token_tree)
			{
				printf("\n>> Ejecutando comandos...\n");
				exe_minishell_recursive(shell->token_tree);
			}
		}

		// Liberar memoria
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

	// Inicializar shell
	ft_bzero(&shell, sizeof(t_shell));
	import_env(&shell, envp); // Importar variables de entorno

	// Configurar manejadores de señales
	//set_sig_handler(SIG_IGN, 1);

	// Iniciar bucle principal
	main_loop(&shell);
	return (EXIT_SUCCESS);
}


