/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:37:16 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/15 19:03:36 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

t_token	*create_new_token(char	*line, t_shell	*shell)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	token->shell = shell;
	token->line = line;
	return (token);
}

void	add_new_token(t_tree	*tree, char	*line, t_shell	*shell)
{
	if (!tree->left)
	{
		tree->left = ft_tree_create_node(tree->data);
		tree->data = create_new_token(line, shell);
	}
	else if (!tree->right)
		tree->right = ft_tree_create_node(create_new_token(line, shell));
	else
		add_new_token(tree->right, line, shell);
}

void	get_token(t_automata *a, void *data)
{
	t_shell	*shell;
	char	*substr;
	char	*trim;

	shell = (t_shell *)data;
	substr = ft_substr(a->str, a->j, a->i - a->j);
	trim = ft_strtrim(substr, " ");
	free(substr);
	a->j = a->i;
	if (!shell->token_tree)
		shell->token_tree = ft_tree_create_node(create_new_token(trim, shell));
	else
		add_new_token(shell->token_tree, trim, shell);
}