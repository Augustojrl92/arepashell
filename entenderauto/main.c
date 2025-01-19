#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

// Liberar memoria asociada con un token
void free_token(void *data)
{
    t_token *token = (t_token *)data;
    if (!token)
        return;
    free(token->line);
    free(token->cmd);
    if (token->args)
        ft_free_sarray(token->args);
    if (token->outfiles)
        ft_free_sarray(token->outfiles);
    if (token->infiles)
        ft_free_sarray(token->infiles);
    if (token->heredoc)
        ft_free_sarray(token->heredoc);
    free(token);
}

// Liberar el árbol de tokens
void free_tree(t_shell *shell, t_tree *tree)
{
    if (!tree)
        return;
    free_tree(shell, tree->left);
    free_token(tree->data);
    free_tree(shell, tree->right);
    free(tree);
    shell->token_tree = NULL;
}

// -------------------------------------------------------------------------- //
// 1) NUEVA FUNCIÓN: Imprimir los tokens de manera SECUENCIAL (in-order)
//    mostrando cmd, args, infiles, outfiles, etc.
// -------------------------------------------------------------------------- //

static void print_token_info(t_token *token, int index)
{
    // Encabezado
    printf("%d) Token \"%s\"\n", index, token->line);

    // Si es solo un pipe "|"
    if (ft_samestr(token->line, "|"))
    {
        printf("   (solo indica pipe)\n\n");
        return;
    }
    // Si es un operador de salida ">"
    if (ft_samestr(token->line, ">"))
    {
        printf("   (operador de salida)\n\n");
        return;
    }
    // Si no, imprimimos la info detallada
    if (token->cmd)
        printf("   cmd       = \"%s\"\n", token->cmd);

    // args
    if (token->args)
    {
        printf("   args      = [");
        for (int i = 0; token->args[i]; i++)
        {
            printf("\"%s\"", token->args[i]);
            if (token->args[i + 1])
                printf(", ");
        }
        printf("]\n");
    }
    else
        printf("   args      = NULL\n");

    // infiles
    if (!token->infiles)
        printf("   infiles   = NULL\n");
    else
    {
        printf("   infiles   = [");
        for (int i = 0; token->infiles[i]; i++)
        {
            printf("\"%s\"", token->infiles[i]);
            if (token->infiles[i + 1])
                printf(", ");
        }
        printf("]\n");
    }

    // outfiles
    if (!token->outfiles)
        printf("   outfiles  = NULL\n");
    else
    {
        printf("   outfiles  = [");
        for (int i = 0; token->outfiles[i]; i++)
        {
            printf("\"%s\"", token->outfiles[i]);
            if (token->outfiles[i + 1])
                printf(", ");
        }
        printf("]\n");
    }

    printf("\n");
}

/**
 * Recorre el árbol en orden (in-order) para imprimir
 * secuencialmente los tokens:
 *  1) Token "ls -l"
 *  2) Token "|"
 *  3) Token "grep txt"
 *  ...
 */
void print_tokens_in_order(t_tree *node, int *index)
{
    if (!node)
        return;
    // Visitar subárbol izquierdo
    print_tokens_in_order(node->left, index);

    // Imprimir el nodo actual
    t_token *token = (t_token *)node->data;
    if (token)
        print_token_info(token, (*index)++);

    // Visitar subárbol derecho
    print_tokens_in_order(node->right, index);
}

// -------------------------------------------------------------------------- //
//            Funciones que ya tenías: process_tokens, main_loop, etc.
// -------------------------------------------------------------------------- //

// Procesar nodos del árbol con el tokenizer
void process_tokens(t_tree *node, t_shell *shell)
{
    if (!node)
        return;
    process_tokens(node->left, shell);

    t_token *token = (t_token *)node->data;
    if (token && token->line)
    {
        // Inicializar y ejecutar el tokenizer
        tokenizer_automata_init(&shell->tokenizer, token);
        shell->tokenizer.str = token->line;
        evaluate(&shell->tokenizer);
        free_alph_err(&shell->tokenizer);
    }
    process_tokens(node->right, shell);
}

// Bucle principal del minishell
void main_loop(t_shell *shell)
{
    while (1)
    {
        printf("\n=== Minishell ===\n");

        // 1) Procesar entrada del usuario (split)
        if (split_in_token_lines(shell))
        {
            // 2) Tokenizar cada nodo del árbol (tokenizer)
            process_tokens(shell->token_tree, shell);

            // 3) Mostrar tokens de forma secuencial (in-order) con enumeración
            printf("\n>> Tokens en orden:\n");
            int index = 1;
            print_tokens_in_order(shell->token_tree, &index);
        }

        // Liberar recursos (árbol, strings, etc.)
        ft_free_sarray(shell->default_env);
        shell->default_env = NULL;
        ft_free_sarray(shell->path_var);
        shell->path_var = NULL;
        free_tree(shell, shell->token_tree);
        free(shell->splitter.str);
        shell->splitter.str = NULL;
    }
}

// Función principal
int main(int ac, char **av, char **envp)
{
    t_shell shell;

    (void)ac;
    (void)av;
    (void)envp; // No usamos envp aquí; si quieres setear variables de entorno, lo harías aparte

    // Inicializar la estructura shell con ceros
    ft_bzero(&shell, sizeof(t_shell));

    // Iniciar el bucle principal
    main_loop(&shell);

    return (EXIT_SUCCESS);
}
