/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_insert_r.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:07:57 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/29 21:12:25 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree	*ft_tree_insert_r(t_tree	*root_node, void	*content)
{
	root_node->right = ft_tree_create_node(content);
	return (root_node->right);
}
