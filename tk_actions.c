/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:09:28 by aurodrig          #+#    #+#             */
/*   Updated: 2025/01/07 05:09:31 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	set_infile(t_automata	*a, void	*data)
{
	t_token	*token;
	char	*infile;
	//char	*temp_filename;

	token = (t_token *)data;
	infile = get_next_word(a);
	if (a->ostate == TK_HEREDOC)
	{
		//printf(">> [set_infile] Heredoc detectado. Ignorado temporalmente.\n");
		token->infiles = ft_add_to_sarray(token->infiles, "heredoc_ignored");
	}
	else
		token->infiles = ft_add_to_sarray(token->infiles, infile);
	free(infile);
}

void	set_outfile(t_automata	*a, void	*data)
{
	t_token	*token;
	char	*outfile;

	token = (t_token *)data;
	outfile = get_next_word(a);
	token->outfiles = ft_add_to_sarray(token->outfiles, outfile);
	if (a->ostate == TK_APPEND)
		token->append = TRUE;
	else
		token->append = FALSE;
	free(outfile);
}

void	set_arg(t_automata	*a, void	*data)
{
	t_token		*token;
	char		*arg;

	token = (t_token *)data;
	arg = get_next_word(a);
	token->args = ft_add_to_sarray(token->args, arg);
	if (!token->cmd)
		token->cmd = ft_strdup(arg);
	free(arg);
}