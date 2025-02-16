/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:57:32 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 16:11:08 by aurodrig         ###   ########.fr       */
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
