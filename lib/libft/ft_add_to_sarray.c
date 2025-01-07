/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_sarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:12:06 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/27 23:05:43 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sarraysize(char **array)
{
	int	count;

	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}

char	**ft_add_to_sarray(char	**array, char	*str)
{
	int		i;
	char	**new_array;

	if (!str)
		return (array);
	i = 0;
	if (array)
		while (array[i])
			i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (array)
	{
		i = 0;
		while (array[i])
		{
			new_array[i] = ft_strdup(array[i]);
			free(array[i]);
			i++;
		}
		free(array);
	}
	new_array[i++] = ft_strdup(str);
	new_array[i] = NULL;
	return (new_array);
}
