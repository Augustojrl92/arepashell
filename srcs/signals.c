/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:40:48 by layala-s          #+#    #+#             */
/*   Updated: 2025/02/12 15:06:38 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sighandler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal_data = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	do_signal(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_handler(int signum)
{
	(void)signum;
	g_signal_data = SIGINT;
	signal(SIGINT, SIG_DFL);
	exit(0);
}
