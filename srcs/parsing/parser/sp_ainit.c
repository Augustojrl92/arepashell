/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_ainit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:08:58 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/24 12:34:45 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// Inicializa el alfabeto (caracteres reconocidos por el autómata)
void	splitter_alphabet_init(t_automata *a)
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

int	splitter_get_state(int i, int j)
{
	const int	states[][7] = {
	{0, 8, 2, 4, 6, 7, 11},
	{12, 8, 2, 4, 6, 7, 11},
	{9, 8, 3, 8, 6, 7, 11},
	{9, 8, 8, 8, 6, 7, 11},
	{9, 8, 8, 5, 6, 7, 11},
	{9, 8, 8, 8, 6, 7, 11},
	{6, 6, 6, 6, 10, 6, 6},
	{7, 7, 7, 7, 7, 10, 7},
	{8, 8, 8, 8, 8, 8, 8},
	{9, 8, 8, 8, 6, 7, 11},
	{10, 1, 2, 4, 6, 7, 11},
	{10, 1, 2, 4, 6, 7, 11},
	{12, 8, 2, 4, 6, 7, 11},
	};

	return (states[i][j]);
}

void	splitter_errors_init(t_automata *a)
{
	a->errors = malloc(11 * (sizeof(char *)));
	a->errors[0] = ft_strdup("\033[B");
	a->errors[1] = ft_strdup("Pipe Open\n");
	a->errors[2] = ft_strdup("Less Open\n");
	a->errors[3] = ft_strdup("Heredoc Open\n");
	a->errors[4] = ft_strdup("Great Open\n");
	a->errors[5] = ft_strdup("Append Open\n");
	a->errors[6] = ft_strdup("\" Open\n");
	a->errors[7] = ft_strdup("\' Open\n");
	a->errors[8] = ft_strdup("Invalid Input\n");
	a->errors[9] = ft_strdup("Open operator\n");
	a->errors[10] = NULL;
	a->errorlen = 9;
}

void	splitter_sactions_init(t_automata *a)
{
	(void)a;
}

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
