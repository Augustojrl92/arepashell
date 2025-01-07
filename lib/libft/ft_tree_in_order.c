/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_in_order.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 22:53:20 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/13 22:34:34 by jlara-na         ###   ########.fr       */
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
