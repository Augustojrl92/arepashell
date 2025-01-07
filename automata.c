/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:06:56 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/07 05:06:57 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

// Función para obtener el índice del carácter en el alfabeto
int	idx(char *alphabet[], char c)
{
	int	i;

	//printf(">> idx: Buscando '%c' en el alfabeto...\n", c); // Debug
	i = -1;
	while (alphabet[++i])
	{
		//printf(">> idx: Comparando con '%s'\n", alphabet[i]); // Debug
		if (ft_chrpos(alphabet[i], c) != -1)
		{
			//printf(">> idx: Encontrado en posición %d\n", i); // Debug
			return (i);
		}
	}
	//printf(">> idx: No encontrado, devolviendo %d\n", i); // Debug
	return (i);
}

// Función para evaluar la entrada con el autómata
int	evaluate(t_automata *a)
{
	//printf(">> evaluate: Iniciando evaluación...\n"); // Debug
	a->ostate = 0;
	a->i = -1;

	if (!a->alphabet || !a->str) // Verificación de inicialización
	{
		//printf(">> evaluate: Error - Alphabet o str no inicializados.\n");
		return (-1);
	}

	while (++a->i < (int)ft_strlen(a->str))
	{
		//printf(">> evaluate: Procesando carácter '%c' en posición %d\n", a->str[a->i], a->i); // Debug
		int index = idx(a->alphabet, a->str[a->i]); // Llama a idx
		a->state = a->get_state(a->state, index);

		//printf(">> evaluate: Estado actual: %d, Estado anterior: %d\n", a->state, a->ostate); // Debug

		if (a->fsa[a->state])
		{
			//printf(">> evaluate: Ejecutando acción de estado fsa[%d]\n", a->state); // Debug
			a->fsa[a->state](a, a->data);
		}
		if (a->fta[a->ostate][a->state])
		{
			//printf(">> evaluate: Ejecutando acción de transición fta[%d][%d]\n", a->ostate, a->state); // Debug
			a->fta[a->ostate][a->state](a, a->data);
		}
		a->ostate = a->state;
	}
	//printf(">> evaluate: Evaluación terminada. Estado final: %d\n", a->state); // Debug
	return (a->state);
}

// Función para liberar memoria usada en alfabetos y errores
void	free_alph_err(t_automata *a)
{
	int	i;

	//printf(">> free_alph_err: Liberando memoria de alphabet...\n"); // Debug
	i = -1;
	if (a->alphabet)
	{
		while (a->alphabet[++i])
		{
			//printf(">> free_alph_err: Liberando '%s'\n", a->alphabet[i]); // Debug
			free(a->alphabet[i]);
		}
		free(a->alphabet);
	}

	//printf(">> free_alph_err: Liberando memoria de errors...\n"); // Debug
	i = -1;
	if (a->errors)
	{
		while (a->errors[++i])
		{
			//printf(">> free_alph_err: Liberando '%s'\n", a->errors[i]); // Debug
			free(a->errors[i]);
		}
		free(a->errors);
	}
	//printf(">> free_alph_err: Memoria liberada correctamente.\n"); // Debug
}

