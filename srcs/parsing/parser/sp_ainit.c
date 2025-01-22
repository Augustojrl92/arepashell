/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_ainit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:08:58 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/20 14:21:58 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// Inicializa el alfabeto (caracteres reconocidos por el autómata)
void splitter_alphabet_init(t_automata *a)
{
    a->alphabet = malloc(7 * (sizeof(char *)));
    a->alphabet[0] = ft_strdup(" \t\n");
    a->alphabet[1] = ft_strdup("|");
    a->alphabet[2] = ft_strdup("<");
    a->alphabet[3] = ft_strdup(">");
    a->alphabet[4] = ft_strdup("\"");
    a->alphabet[5] = ft_strdup("\'");
    a->alphabet[6] = NULL;
}

// Función para obtener el estado según la matriz
int splitter_get_state(int i, int j)
{
    const int	states[][7] = {
        {0, 8, 2, 4, 6, 7, 11},		// 0  Empty
        {12, 8, 2, 4, 6, 7, 11},	// 1  Pipe Open
        {9, 8, 3, 8, 6, 7, 11},		// 2  Less Open
        {9, 8, 8, 8, 6, 7, 11},		// 3  Heredoc Open
        {9, 8, 8, 5, 6, 7, 11},		// 4  Greater Open
        {9, 8, 8, 8, 6, 7, 11},		// 5  Append Open
        {6, 6, 6, 6, 10, 6, 6},		// 6  Open double quotes
        {7, 7, 7, 7, 7, 10, 7},		// 7  Open single quotes
        {8, 8, 8, 8, 8, 8, 8},		// 8  Invalid input
        {9, 8, 8, 8, 6, 7, 11},		// 9 Spaces after key
        {10, 1, 2, 4, 6, 7, 11},	// 10 Spaces between words
        {10, 1, 2, 4, 6, 7, 11},	// 11 Comands
        {12, 8, 2, 4, 6, 7, 11},	// 12 Spaces after pipe
    };
    return (states[i][j]);
}

// Inicializa los errores
void splitter_errors_init(t_automata *a)
{
    a->errors = malloc(11 * (sizeof(char *)));
    a->errors[0] = ft_strdup("\033[B");
    a->errors[1] = ft_strdup("Pipe Open");
    a->errors[2] = ft_strdup("Less Open");;
    a->errors[3] = ft_strdup("Heredoc Open");
    a->errors[4] = ft_strdup("Great Open");
    a->errors[5] = ft_strdup("Append Open");
    a->errors[6] = ft_strdup("\" Open");
    a->errors[7] = ft_strdup("\' Open");
    a->errors[8] = ft_strdup("Invalid Input");
	a->errors[9] = ft_strdup("Open operator");
    a->errors[10] = NULL;
    a->errorlen = 9;
}

// Inicializa acciones de estado (actualmente vacías)
void splitter_sactions_init(t_automata *a)
{
    (void)a;
}

// Inicializa acciones de transición
void	splitter_tactions_init(t_automata *a)
{
	a->fta[SP_PIPE][SP_SPACEPIPE] = get_token;
	a->fta[SP_PIPE][SP_WORDS] = get_token;
	a->fta[SP_PIPE][SP_DOUBLEQ] = get_token;
	a->fta[SP_PIPE][SP_SINGLEQ] = get_token;
	a->fta[SP_PIPE][SP_LESS] = get_token;
	a->fta[SP_PIPE][SP_GREAT] = get_token;
	a->fta[SP_SPACEB][SP_PIPE] = get_token;
	a->fta[SP_SPACEW][SP_PIPE] = get_token;
	a->fta[SP_WORDS][SP_PIPE] = get_token;
}

// Inicialización general del autómata
void splitter_automata_init(t_automata *a, void *data)
{
    ft_bzero(a, sizeof(t_automata));
    a->data = data;

    splitter_alphabet_init(a);
    splitter_errors_init(a);
    splitter_sactions_init(a);
    splitter_tactions_init(a);

    a->get_state = splitter_get_state;
}