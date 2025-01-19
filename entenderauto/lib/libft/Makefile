# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 17:02:15 by jlara-na          #+#    #+#              #
#    Updated: 2024/09/26 23:49:27 by jlara-na         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MAKEFLAGS := --quiet

FILES_C =	ft_isalpha.c				\
			ft_isdigit.c				\
			ft_isalnum.c				\
			ft_isascii.c				\
			ft_isprint.c				\
			ft_strlen.c					\
			ft_memset.c					\
			ft_bzero.c					\
			ft_memcpy.c					\
			ft_memmove.c				\
			ft_strlcpy.c				\
			ft_strlcat.c				\
			ft_toupper.c				\
			ft_tolower.c				\
			ft_strchr.c					\
			ft_strrchr.c				\
			ft_strncmp.c				\
			ft_memchr.c					\
			ft_memcmp.c					\
			ft_strnstr.c				\
			ft_atoi.c					\
			ft_atoi_base.c				\
			ft_calloc.c					\
			ft_strdup.c					\
			ft_substr.c					\
			ft_strjoin.c				\
			ft_strtrim.c				\
			ft_split.c					\
			ft_itoa.c					\
			ft_strmapi.c				\
			ft_striteri.c				\
			ft_putchar_fd.c				\
			ft_putstr_fd.c				\
			ft_putendl_fd.c				\
			ft_putnbr_fd.c				\
			ft_lstfind.c				\
			ft_lstnew_bonus.c			\
			ft_lstadd_front_bonus.c		\
			ft_lstsize_bonus.c			\
			ft_lstlast_bonus.c			\
			ft_lstadd_back_bonus.c		\
			ft_lstdelone_bonus.c		\
			ft_lstclear_bonus.c			\
			ft_lstiter_bonus.c			\
			ft_lstmap_bonus.c			\
			ft_swap.c					\
			get_next_line.c				\
			ft_tree_create_node.c		\
			ft_tree_del_node.c			\
			ft_tree_insert_l.c			\
			ft_tree_insert_r.c			\
			ft_tree_post_order.c		\
			ft_tree_pre_order.c			\
			ft_tree_in_order.c			\
			ft_tree_size.c				\
			ft_chrpos.c					\
			ft_add_to_sarray.c			\
			ft_free_sarray.c			\

FILES_O = $(FILES_C:.c=.o)

FILES_O_BONUS = $(FILES_C_BONUS:.c=.o) 

CC = gcc -Werror -Wextra -Wall

all: $(NAME)

msg:
	@echo "\033[2K\033[0;33;5m\033[0;33mCOMPILING:		⚙ LIBFT\033[0m\033[1A"

$(NAME): msg $(FILES_O)
	@ar -rc $(NAME) $(FILES_O)

clean:
	rm -f $(FILES_O) $(FILES_O_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

bonus:
	make "FILES_C = $(FILES_C_BONUS)"

.PHONY: all clean fclean re bonus
