/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:15:13 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/27 23:40:49 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				len;
	int				sign;
	long long int	base;

	i = 0;
	len = 0;
	sign = 1;
	base = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = 1 - 2 * (str[i++] == '-');
	while (str[i] >= '0' && str[i] <= '9')
	{
		base = 10 * base + (str[i++] - '0');
		len++;
		if ((base > 2147483647 && sign == 1)
			|| (base > 2147483648 && sign == -1))
			return (0);
	}
	return (base * sign);
}
