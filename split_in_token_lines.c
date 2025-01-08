/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_token_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:09:14 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/08 20:38:03 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int	split_in_token_lines(t_shell	*shell)
{
	int		a_state;
	char	*input;

	// Usar un prompt fijo en lugar de generar uno dinámico
	printf("arepashell> "); // Prompt fijo
	input = readline("");  // Lee entrada del usuario

	// Manejar entrada nula (Ctrl+D)
	if (input == NULL)
	{
		printf(MSG_BYE);
		exit(EXIT_SUCCESS);
	}

	// Añadir entrada al historial
	add_history(input);

	// Inicializar el autómata
	splitter_automata_init(&shell->splitter, shell);
	shell->splitter.str = input;

	// Evaluar la entrada con el autómata
	a_state = evaluate(&shell->splitter);
	get_token(&shell->splitter, shell);

	// Verificar errores
	if (a_state > shell->splitter.errorlen)
		return (free_alph_err(&shell->splitter), 1);
	else
	{
		printf( "%s\n", shell->splitter.errors[a_state]);
		return (free_alph_err(&shell->splitter), 0);
	}
}
