/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_del_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:33:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/13 22:36:49 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_del_node(t_tree *node, void (*del)(void*))
{
	if (!node || !del)
		return ;
	del(node->data);
	free(node);
}
