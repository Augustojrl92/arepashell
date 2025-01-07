/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:25:57 by jlara-na          #+#    #+#             */
/*   Updated: 2022/06/30 17:26:07 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*tmp;

	if (lst && f)
	{
		res = ft_lstnew(f(lst->content));
		tmp = res;
		while (lst->next)
		{
			lst = lst->next;
			tmp->next = ft_lstnew(f(lst->content));
			if (!tmp->next)
			{
				ft_lstclear(&res, del);
				return (NULL);
			}
			tmp = tmp->next;
		}
		return (res);
	}
	return (NULL);
}
