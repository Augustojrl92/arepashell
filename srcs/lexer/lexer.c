#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef enum e_states {
    EMPTY,          // 0
    INVALID,        // 1
    NOT_OPERATOR,   // 2
    QUOT,           // 3
    ENDQ,           // 4
    PIPE,           // 5
    RED_IN_QUOTE,   // 6
    RED_IN_D_QUOTE, // 7
    RED_OUT_QUOTE,  // 8
    RED_OUT_D_QUOTE,// 9
    LAST            // 10
} t_states;

int get_state(int prev, int curr) {
    static int states[][11] = {
        {0, 1, 2, 3, 1, 1, 6, 1, 8, 9, 10}, // EMPTY
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  // INVALID
        {1, 1, 2, 3, 1, 5, 6, 1, 8, 1, 10}, // NOT_OPERATOR
        {1, 1, 3, 1, 4, 3, 3, 1, 3, 1, 1},  // QUOT
        {1, 1, 2, 3, 1, 5, 6, 1, 8, 1, 10}, // ENDQ
        {1, 1, 2, 3, 1, 1, 6, 1, 8, 1, 10}, // PIPE
        {1, 1, 2, 3, 1, 1, 1, 7, 1, 1, 1},  // RED_IN_QUOTE
        {1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 10}, // RED_IN_D_QUOTE
        {1, 1, 2, 3, 1, 1, 1, 1, 1, 9, 1},  // RED_OUT_QUOTE
        {1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1},  // RED_OUT_D_QUOTE
        {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10} // LAST
    };
    return (states[prev][curr]);
}

int is_operator(char c) {
    return (c == '&' || c == ';' || c == '|' || c == '<' || c == '>');
}

void check_quote_state(const char *s, int *prev, char *prev_quote, int *curr)
{
    if (*prev == QUOT && *s == *prev_quote)
	{
        *curr = ENDQ;
        *prev_quote = '\0';
    }
	else if (*prev == QUOT)
        *curr = NOT_OPERATOR;
	else
	{
        *prev_quote = *s;
        *curr = QUOT;
    }
}
int	check_operators(const char *str, int *prev, int curr)
{
	    if (*str == '&' && str[1] == '&' && str[2] == '&')
            return (INVALID);
        if (*str == ';' && (*(str + 1) == ';' || *prev == EMPTY)) 
            return (INVALID);
        if (*str == '<' || *str == '>') 
		{
            if (*prev == RED_IN_QUOTE || *prev == RED_OUT_QUOTE) 
                return (INVALID);
            if (*str == '<')
				curr = RED_IN_QUOTE;
			else
				curr = RED_OUT_QUOTE;
        }
        if (*str == '|')
            curr = PIPE;
		return (curr);
}
int check_states(const char *str, int *prev, char *prev_quote)
{
    int curr = NOT_OPERATOR;

    if (is_operator(*str))
	{
		curr = check_operators(str, prev, curr);
    } else if (*str == '\'' || *str == '"')
	{
        check_quote_state(str, prev, prev_quote, &curr);
    } else if (*str == '\0') {
        curr = LAST;
    }
    return (curr);
}

int check_input(char *str)
{
    int prev = EMPTY;
    int curr;
    char prev_quote = '\0';

    while (1)
	{
        while (*str == ' ')
            str++;
        curr = check_states(str, &prev, &prev_quote);
        curr = get_state(prev, curr);
        if (curr == INVALID) {
            write(2, "invalid syntax\n", 15);
            return (0);
        }
        if (curr == LAST)
            return (1);
        prev = curr;
        str++;
    }
}
int main() {
    char *test_cases[] = {
        "echo 'hello world'",          // 1 Entrada válida: comillas simples.
        "echo \"hello world\"",        // 2 Entrada válida: comillas dobles.
        "cat < input.txt > output.txt",// 3 Entrada válida: redirecciones.
        "ls | grep '.c' | sort",       // 4 Entrada válida: tuberías.
        "echo 'unterminated",          // 5 Inválida: comillas simples no cerradas.
        "echo \"unterminated",         // 6 Inválida: comillas dobles no cerradas.
        "cat | | grep",                // 7 Inválida: tuberías consecutivas.
        "<< infile.txt",               // 8 Entrada válida: redirección múltiple válida.
        "echo | grep",                 // 9 Entrada válida: tubería simple.
        "cat < infile > outfile | grep text", //10 Entrada válida: combinación de redirección y tubería.
        "cat > outfile << infile",     // 11 Inválida: redirección mal formada.
        "echo \"hello | world\"",      // 12 Entrada válida: comillas con tubería dentro.
        "echo 'hello > world'",        // 13Entrada válida: comillas con redirección dentro.
        "echo hello && ls || cat",     // 14 Entrada válida: operadores válidos.
        "echo hello &&& ls",           // 15 Inválida: operador no permitido.
        "echo $PATH",                // 16 Inválida: punto y coma inicial.
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("Test case %d: %s\n", i + 1, test_cases[i]);
        int result = check_input(test_cases[i]);
        printf("Result: %s\n\n", result ? "Valid" : "Invalid");
    }
    return 0;
}

