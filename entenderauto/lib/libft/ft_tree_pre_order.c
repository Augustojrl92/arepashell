/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_pre_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 22:49:51 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/13 22:36:23 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_pre_order(t_tree *node, void (*ft)(void*))
{
	if (node != NULL)
	{
		ft(node->data);
		ft_tree_pre_order(node->left, ft);
		ft_tree_pre_order(node->right, ft);
	}
}
