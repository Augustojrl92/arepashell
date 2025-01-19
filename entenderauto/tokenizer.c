/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:09:50 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/07 05:09:51 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	tokenize_node(void	*token_ptr, void	*shell_ptr)
{
	t_shell	*shell;
	t_token	*token;

	shell = (t_shell *)shell_ptr;
	token = (t_token *)token_ptr;
	if (ft_samestr(token->line, "|"))
		return ;
	tokenizer_automata_init(&shell->tokenizer, token);
	shell->tokenizer.str = token->line;
	evaluate(&shell->tokenizer);
	free_alph_err(&shell->tokenizer);
}
