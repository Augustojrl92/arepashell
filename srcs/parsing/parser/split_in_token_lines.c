/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_token_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:09:14 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/22 10:51:05 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	splitter_automata_init(t_automata *a, void *data)
{
	ft_bzero(a, sizeof(t_automata));
	a->data = data;
	splitter_alphabet_init(a);
	splitter_errors_init(a);
	splitter_sactions_init(a);
	splitter_tactions_init(a);
	a->get_state = splitter_get_state;
}

int	split_in_token_lines(t_shell	*shell)
{
	int		a_state;
	char	*input;

	input = readline("\033[1;33;43marepashell>\033[0;0m ");
	if (input == NULL)
	{
		printf(MSG_BYE);
		exit(EXIT_SUCCESS);
	}
	add_history(input);
	splitter_automata_init(&shell->splitter, shell);
	shell->splitter.str = input;
	a_state = evaluate(&shell->splitter);
	get_token(&shell->splitter, shell);
	if (a_state > shell->splitter.errorlen)
		return (free_alph_err(&shell->splitter), 1);
	else
	{
		printf("%s", shell->splitter.errors[a_state]);
		return (free_alph_err(&shell->splitter), 0);
	}
}
