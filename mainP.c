#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para imprimir el árbol sintáctico (recorrido en preorden)
void	print_tree(t_tree *node, int depth)
{
	if (!node)
		return;

	// Indenta según la profundidad
	for (int i = 0; i < depth; i++)
		printf("  ");
	
	// Verifica si el nodo tiene datos válidos
	t_token *token = (t_token *)node->data;
	if (token && token->line)
		printf("- Token: '%s'\n", token->line);
	else
		printf("- Nodo inválido o vacío.\n");

	// Recurre en los nodos hijos
	print_tree(node->left, depth + 1);
	print_tree(node->right, depth + 1);
}

// Función principal
int	main(void)
{
	t_automata	a;              // Estructura del autómata
	t_shell		shell;          // Contexto del shell
	int		result;         // Resultado del estado final

	// Inicializamos el shell y el árbol sintáctico
	shell.token_tree = NULL;

	while (1)
	{
		// Re-inicializar el autómata antes de procesar cada entrada
		printf(">> Inicializando autómata...\n");
		splitter_automata_init(&a, &shell);

		// Procesar línea de tokens
		if (!split_in_token_lines(&shell))
		{
			printf(">> Error al procesar línea de tokens.\n");
			continue;
		}

		// Validar autómata antes de evaluar
		if (!shell.splitter.str || !shell.splitter.alphabet)
		{
			printf(">> Error - Alphabet o str no inicializados después de reinicio.\n");
			continue;
		}

		// Evaluar entrada
		printf(">> Evaluando entrada: '%s'\n", shell.splitter.str);
		result = evaluate(&a);

		// Procesar tokens
		printf(">> Procesando tokens...\n");
		if (a.j >= a.i || a.i > (int)strlen(a.str))
		{
			printf(">> [get_token] Error: Índices fuera de rango (j: %d, i: %d).\n", a.j, a.i);
			continue;
		}
		get_token(&shell.splitter, &shell);

		// Verificar errores
		if (result >= 0 && result < a.errorlen && a.errors[result])
		{
			printf(">> Error detectado: %s\n", a.errors[result]);
			continue;
		}
		else
		{
			printf(">> Evaluación completada sin errores.\n");
		}

		// Mostrar árbol sintáctico
		if (shell.token_tree)
		{
			printf("\n>> Árbol sintáctico generado:\n");
			print_tree(shell.token_tree, 0);
		}
		else
		{
			printf("\n>> No se generó ningún árbol sintáctico.\n");
		}

		// Restaurar índices y estado después de procesar tokens
		printf(">> Restaurando índices y estados...\n");
		shell.splitter.i = -1;
		shell.splitter.j = 0;
		shell.splitter.state = 0;
		shell.splitter.ostate = 0;

		// Liberar solo la cadena de entrada, manteniendo el alfabeto y errores
		free(shell.splitter.str);
		shell.splitter.str = NULL;
	}

	// Liberar memoria al salir
	free_alph_err(&a);
	printf(">> Memoria liberada correctamente.\n");

	return (0);
}
