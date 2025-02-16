/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_create_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:55:41 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:21:53 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree	*ft_tree_create_node(void	*content)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_tree));
	new_node->data = NULL;
	new_node->data = content;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
