/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:23:09 by layala-s          #+#    #+#             */
/*   Updated: 2025/01/27 12:23:10 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_n_flag(const char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	do_last_folder(t_shell *shell, char *cwd)
{
	printf("%s\n", shell->last_path);
	chdir(shell->last_path);
	if (shell->last_path)
		free(shell->last_path);
	shell->last_path = ft_strdup(cwd);
	if (!shell->last_path)
		perror("cd: memory allocation failed");
}
