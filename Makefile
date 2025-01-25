# Nombre del ejecutable
NAME = minishell

# Compilador y flags
CC = gcc
CFLAGS = -fsanitize=leak -Wall -Wextra -Werror -g3 -Iincludes

# Comando para eliminar
RM = rm -rf

# Directorios
OBJ_DIR = obj/
SRC_DIR = src/
LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Archivos fuente iniciales
SRCS = main.c \
	./srcs/parsing/automata.c \
	./srcs/parsing/parser/sp_ainit.c \
	./srcs/parsing/parser/sp_actions.c \
	./srcs/parsing/parser/split_in_token_lines.c \
	./srcs/parsing/tokenizer/tk_ainit.c \
	./srcs/parsing/tokenizer/tk_actions.c \
	./srcs/parsing/tokenizer/tokenizer.c \
	./srcs/builtins/cd_utils.c \
	./srcs/builtins/echo_utils.c \
	./srcs/builtins/exit_utils.c \
	actions_utils.c \
	import_env.c \
	search_utils.c \
	./srcs/executors/exe_builtins.c \
	./srcs/executors/exe_cmd.c \
	./srcs/executors/exe_tokens.c \
	./srcs/executors/exe_utils.c \
	builtin.c \
	stdin_redir.c \
	env.c \
	./srcs/expansors/expander.c \
	./srcs/expansors/exp_actions.c \
	./srcs/expansors/exp_init.c \
	export.c \

# Archivos objeto (ubicados en obj/)
OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

# Colores para salida
CYAN = \033[0;96m
DEF_COLOR = \033[0;49m

# Regla para compilar el programa
$(NAME): $(LIBFT) $(OBJ)
	@echo "$(CYAN) ☕ Building Minishell... ☕ $(DEF_COLOR)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(CYAN) ✨ Build complete! ✨ $(DEF_COLOR)"

# Regla para compilar archivos fuente en objetos
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) -c $< -o $@


# Regla para compilar libft
$(LIBFT):
	@echo "$(CYAN) 🛠️  Compiling libft... 🛠️ $(DEF_COLOR)"
	@$(MAKE) -C $(LIBFT_DIR)

# Regla para compilar todo
all: $(NAME)

# Limpiar archivos compilados
clean:
	@echo "$(CYAN) 🍩 Cleaning object files... 🍩 $(DEF_COLOR)"
	$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Limpiar todo
fclean: clean
	@echo "$(CYAN) ✨ Removing executable and libft... ✨ $(DEF_COLOR)"
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Reconstruir
re: fclean all

.PHONY: all clean fclean re
