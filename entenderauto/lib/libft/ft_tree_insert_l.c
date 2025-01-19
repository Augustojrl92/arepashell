/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_insert_l.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:07:06 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/29 21:12:24 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree	*ft_tree_insert_l(t_tree	*root_node, void	*content)
{
	root_node->left = ft_tree_create_node(content);
	return (root_node->left);
}
