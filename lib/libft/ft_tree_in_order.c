/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_in_order.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:55:41 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:22:37 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_in_order(t_tree *node, void (*ft)(void*))
{
	if (node != NULL)
	{
		ft_tree_in_order(node->left, ft);
		ft(node->data);
		ft_tree_in_order(node->right, ft);
	}
}

void	ft_tree_in_order_arg(t_tree *n, void (*ft)(void*, void*), void	*arg)
{
	if (n != NULL)
	{
		ft_tree_in_order_arg(n->left, ft, arg);
		ft(n->data, arg);
		ft_tree_in_order_arg(n->right, ft, arg);
	}
}
