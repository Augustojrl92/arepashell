/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_pre_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:55:41 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:23:35 by aurodrig         ###   ########.fr       */
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
