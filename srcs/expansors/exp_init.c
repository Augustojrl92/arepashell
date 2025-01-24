/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_actions_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:08:57 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/22 10:33:16 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expander_alphabet_init(t_automata *a)
{
	a->alphabet = malloc(5 * (sizeof(char *)));
	a->alphabet[0] = ft_strdup(" \t\n");
	a->alphabet[1] = ft_strdup("\"");
	a->alphabet[2] = ft_strdup("\'");
	a->alphabet[3] = ft_strdup("$");
	a->alphabet[4] = NULL;
}

int	expander_get_state(int i, int j)
{
	const int	states[][5] = {
	{0, 1, 2, 3, 0},	// 0 Looking
	{1, 0, 1, 4, 1},	// 1 Open double quotes
	{2, 2, 0, 2, 2},	// 2 Open single quotes
	{0, 1, 2, 3, 5},	// 3 Dollar outside
	{1, 0, 1, 4, 6},	// 4 Dollar inside 
	{0, 1, 2, 3, 5},	// 5 Name	outside
	{1, 0, 1, 4, 6},	// 6 Name	inside
	};

	return (states[i][j]);
}

void	expander_errors_init(t_automata *a)
{
	(void)a;
}

void	expander_sactions_init(t_automata *a)
{
	a->fsa[EX_DOLLAR_OUT] = insert_var;
	a->fsa[EX_DOLLAR_IN] = insert_var;
}

void	expander_tactions_init(t_automata *a)
{
	a->fta[EX_LOOKING][EX_LOOKING] = insert_chr;
	a->fta[EX_DOUBLEQ][EX_DOUBLEQ] = insert_chr;
	a->fta[EX_SINGLEQ][EX_SINGLEQ] = insert_chr;
	a->fta[EX_DOLLAR_IN][EX_DOUBLEQ] = insert_chr;
	a->fta[EX_NAME_OUT][EX_LOOKING] = insert_chr;
	a->fta[EX_NAME_IN][EX_DOUBLEQ] = insert_chr;
}
