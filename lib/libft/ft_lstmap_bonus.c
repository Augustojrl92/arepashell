/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:57:32 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:12:46 by aurodrig         ###   ########.fr       */
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
