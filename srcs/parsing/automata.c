/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:06:56 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/19 19:39:32 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	idx(char *alphabet[], char c)
{
	int	i;

	i = -1;
	while (alphabet[++i])
	{
		if (ft_chrpos(alphabet[i], c) != -1)
		{
			return (i);
		}
	}
	return (i);
}

// Función para evaluar la entrada con el autómata
int	evaluate(t_automata *a)
{
	a->ostate = 0;
	a->i = -1;
	while (++a->i < (int)ft_strlen(a->str))
	{
		a->state = a->get_state(a->state, idx(a->alphabet, a->str[a->i]));
		if (a->fsa[a->state])
			a->fsa[a->state](a, a->data);
		if (a->fta[a->ostate][a->state])
			a->fta[a->ostate][a->state](a, a->data);
		a->ostate = a->state;
	}
	return (a->state);
}

// Función para liberar memoria usada en alfabetos y errores
void	free_alph_err(t_automata *a)
{
	int	i;

	i = -1;
	if (a->alphabet)
	{
		while (a->alphabet[++i])
		{
			free(a->alphabet[i]);
		}
		free(a->alphabet);
	}
	i = -1;
	if (a->errors)
	{
		while (a->errors[++i])
		{
			free(a->errors[i]);
		}
		free(a->errors);
	}
}