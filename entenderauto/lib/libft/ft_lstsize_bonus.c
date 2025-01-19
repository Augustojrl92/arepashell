/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:42:31 by jlara-na          #+#    #+#             */
/*   Updated: 2022/06/30 17:35:21 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t			i;
	t_list			*list;

	i = 1;
	if (!lst)
		return (0);
	list = lst;
	while (list->next != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}
