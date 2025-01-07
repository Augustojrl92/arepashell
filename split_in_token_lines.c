/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_token_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:09:14 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/07 05:09:18 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	split_in_token_lines(t_shell *shell)
{
	int		a_state;
	char		input[256];

	// Solicitar entrada manual para pruebas
	printf("Ingrese una cadena para probar el autómata: ");
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")] = 0;

	// Verificar si el usuario desea salir
	if (strcmp(input, "exit") == 0)
	{
		printf(MSG_BYE);
		exit(EXIT_SUCCESS);
	}

	// Inicializar el autómata
	splitter_automata_init(&shell->splitter, shell); // Configura el autómata correctamente

	// Asignar entrada manual como línea del autómata
	shell->splitter.str = strdup(input); // Copia segura de la entrada
	shell->splitter.i = -1;  // Inicializa el índice al comienzo
	shell->splitter.j = 0;   // Reinicia el índice inicial

	// Verificar si el autómata se inicializó correctamente
	if (!shell->splitter.str || !shell->splitter.alphabet)
	{
		//printf(RED ">> Error - Alphabet o str no inicializados.\n" DEFAULT_SGR);
		free_alph_err(&shell->splitter);
		return (0);
	}

	// Evaluar la entrada
	//printf(">> Evaluando entrada: '%s'\n", shell->splitter.str);
	a_state = evaluate(&shell->splitter);

	// Procesar tokens
	//printf(">> Procesando tokens...\n");
	get_token(&shell->splitter, shell);

	// Verificar errores
	if (a_state >= shell->splitter.errorlen) // Validar estado fuera de rango
	{
		free_alph_err(&shell->splitter);
		return (1); // No hay errores
	}
	else
	{
		// Mostrar error si ocurre
		printf("%s\n" , shell->splitter.errors[a_state]);
		free_alph_err(&shell->splitter);
		return (0); // Error detectado
	}
}
