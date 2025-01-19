/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:22:28 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/29 21:30:02 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tree_size(t_tree	*node)
{
	if (node == NULL)
		return (0);
	return (1 + ft_tree_size(node->left) + ft_tree_size(node->right));
}
