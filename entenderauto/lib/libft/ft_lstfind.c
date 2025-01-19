/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:42:19 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/22 03:58:27 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, t_bool (*f)(void *, void *), void *context)
{
	if (!lst || !f || !lst->content)
		return (NULL);
	while (lst)
	{
		if (f(lst->content, context))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
