/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:38:08 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/16 20:28:47 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	adjust_index(int index, int len_arr)
{
	if (index < 0)
		return (0);
	if (index > len_arr)
		return (len_arr);
	return (index);
}

static void	fill_new_array(char **new_arr, char **arr, char **insert, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i < index)
	{
		new_arr[i] = arr[i];
		i++;
	}
	j = 0;
	while (insert && insert[j])
	{
		new_arr[i + j] = ft_strdup(insert[j]);
		j++;
	}
	while (arr[index])
	{
		new_arr[i + j] = arr[index];
		index++;
		j++;
	}
	new_arr[i + j] = NULL;
}

char	**ft_insert_sarray(char **arr, char **insert, int index)
{
	int		len_arr;
	int		len_ins;
	char	**new_arr;

	if (!arr)
		return (NULL);
	len_arr = ft_sarraysize(arr);
	len_ins = ft_sarraysize(insert);
	index = adjust_index(index, len_arr);
	new_arr = malloc(sizeof(char *) * (len_arr + len_ins + 1));
	if (!new_arr)
		return (arr);
	fill_new_array(new_arr, arr, insert, index);
	free(arr);
	return (new_arr);
}
