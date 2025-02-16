/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:55:41 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:23:41 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tree_size(t_tree	*node)
{
	if (node == NULL)
		return (0);
	return (1 + ft_tree_size(node->left) + ft_tree_size(node->right));
}
