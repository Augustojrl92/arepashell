/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:08:00 by aurodrig          #+#    #+#             */
/*   Updated: 2025/02/20 23:00:59 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_path_var(t_shell	*shell)
{
	char	**paths;
	char	*path_value;
	int		i;

	i = -1;
	paths = NULL;
	path_value = find_value(shell->enviroment, "PATH");
	paths = ft_split(path_value, ':');
	free(path_value);
	if (paths)
	{
		while (paths[++i])
			paths[i] = ft_strjoinfree(paths[i], "/", 0);
	}
	return (paths);
}

t_var	*create_var(char *name, char *value)
{
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	free(name);
	free(value);
	return (var);
}

void	free_env(t_shell	*shell)
{
	t_list	*node;
	t_list	*aux;
	t_var	*var;

	node = shell->enviroment;
	while (node)
	{
		var = (t_var *)(node->content);
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		if (var)
			free(var);
		aux = node->next;
		free(node);
		node = aux;
	}
	ft_free_sarray(shell->path_var);
	ft_free_sarray(shell->default_env);
}

void	update_default_env(t_shell	*shell)
{
	t_list	*aux;
	t_var	*var;
	char	*full_var;

	full_var = NULL;
	var = NULL;
	aux = shell->enviroment;
	while (aux)
	{
		var = (t_var *)aux->content;
		full_var = ft_strjoin(var->name, "=");
		full_var = ft_strjoinfree(full_var, var->value, 0);
		shell->default_env = ft_add_to_sarray(shell->default_env, full_var);
		free(full_var);
		aux = aux->next;
	}
}

void	import_env(t_shell	*shell, char **env)
{
	int	i;
	int	j;

	i = -1;
	shell->enviroment = NULL;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
		{
			if (env[i][j] == '=')
				ft_lstadd_back(&shell->enviroment, ft_lstnew(
						create_var(ft_substr(env[i], 0, j),
							ft_substr(env[i], j + 1, INT_MAX))));
		}
	}
}
