/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_ainit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:09:40 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/07 05:09:41 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	tokenizer_alphabet_init(t_automata *a)
{
	a->alphabet = malloc(6 * (sizeof(char *)));
	a->alphabet[0] = ft_strdup(" \t\n");
	a->alphabet[1] = ft_strdup("\"");
	a->alphabet[2] = ft_strdup("\'");
	a->alphabet[3] = ft_strdup("<");
	a->alphabet[4] = ft_strdup(">");
	a->alphabet[5] = NULL;
}

int	tokenizer_get_state(int i, int j)
{
	const int	states[][6] = {
	{0, 1, 2, 6, 8, 10},	// 0 Empty input
	{1, 11, 1, 1, 1, 1},	// 1 Open double quotes
	{2, 2, 11, 2, 2, 2},	// 2 Open single quotes
	{3, 3, 3, 3, 3, 3},		// 3 Invalid input
	{4, 1, 2, 6, 8, 10},	// 4 Spaces without words
	{5, 1, 2, 6, 8, 10},	// 5 Spaces between words
	{4, 1, 2, 7, 8, 10},	// 6 lower found
	{4, 1, 2, 3, 3, 10},	// 7 heredoc
	{4, 1, 2, 3, 9, 10},	// 8 greater found
	{4, 1, 2, 3, 3, 10},	// 9 append
	{5, 1, 2, 6, 8, 10},	// 10 Not operators
	{5, 1, 2, 6, 8, 10},	// 11 End of q
	};

	return (states[i][j]);
}

void	tokenizer_errors_init(t_automata *a)
{
	a->errors = malloc(5 * (sizeof(char *)));
	a->errors[0] = ft_strdup("Empty string.\n");
	a->errors[1] = ft_strdup("\" Open\n");
	a->errors[2] = ft_strdup("\' Open\n");
	a->errors[3] = ft_strdup("Invalid Input tk\n");
	a->errors[4] = NULL;
	a->errorlen = 4;
}

void	tokenizer_sactions_init(t_automata *a)
{
	(void)a;
}

void	tokenizer_tactions_init(t_automata *a)
{
	a->fta[TK_LESS][TK_SPACEB] = set_infile;
	a->fta[TK_LESS][TK_WORDS] = set_infile;
	a->fta[TK_LESS][TK_DOUBLEQ] = set_infile;
	a->fta[TK_LESS][TK_SINGLEQ] = set_infile;
	a->fta[TK_HEREDOC][TK_SPACEB] = set_infile;
	a->fta[TK_HEREDOC][TK_WORDS] = set_infile;
	a->fta[TK_HEREDOC][TK_DOUBLEQ] = set_infile;
	a->fta[TK_HEREDOC][TK_SINGLEQ] = set_infile;
	a->fta[TK_GREAT][TK_SPACEB] = set_outfile;
	a->fta[TK_GREAT][TK_WORDS] = set_outfile;
	a->fta[TK_GREAT][TK_DOUBLEQ] = set_outfile;
	a->fta[TK_GREAT][TK_SINGLEQ] = set_outfile;
	a->fta[TK_APPEND][TK_SPACEB] = set_outfile;
	a->fta[TK_APPEND][TK_WORDS] = set_outfile;
	a->fta[TK_APPEND][TK_DOUBLEQ] = set_outfile;
	a->fta[TK_EMPTY][TK_DOUBLEQ] = set_arg;
	a->fta[TK_EMPTY][TK_SINGLEQ] = set_arg;
	a->fta[TK_EMPTY][TK_WORDS] = set_arg;
	a->fta[TK_SPACEW][TK_WORDS] = set_arg;
	a->fta[TK_SPACEW][TK_DOUBLEQ] = set_arg;
	a->fta[TK_SPACEW][TK_SINGLEQ] = set_arg;
}
