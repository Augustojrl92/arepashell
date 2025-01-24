/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:08:39 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/22 10:37:13 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expander_automata_init(t_automata *a, void *data)
{
	ft_bzero(a, sizeof(t_automata));
	a->data = data;
	expander_alphabet_init(a);
	expander_errors_init(a);
	expander_sactions_init(a);
	expander_tactions_init(a);
	a->get_state = expander_get_state;
}

void	expand_line(t_token	*token, t_shell	*shell, char	**str)
{
	token->data = str;
	expander_automata_init(&shell->expander, token);
	shell->expander.str = ft_strdup(*str);
	free(*str);
	*str = ft_strdup("");
	evaluate(&shell->expander);
	free(shell->expander.str);
	free_alph_err(&shell->expander);
}

void	expand_token(void	*token_ptr, void	*shell_ptr)
{
	t_shell	*shell;
	t_token	*token;
	int		i;

	shell = (t_shell *)shell_ptr;
	token = (t_token *)token_ptr;
	if (token->cmd)
		expand_line(token, shell, &token->cmd);
	i = 0;
	if (token->args)
		while (token->args[i])
			expand_line(token, shell, &token->args[i++]);
	i = 0;
	if (token->outfiles)
		while (token->outfiles[i])
			expand_line(token, shell, &token->outfiles[i++]);
	i = 0;
	if (token->infiles)
		while (token->infiles[i])
			expand_line(token, shell, &token->infiles[i++]);
}
