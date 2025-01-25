/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layala-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:48:57 by layala-s          #+#    #+#             */
/*   Updated: 2025/01/24 12:01:48 by layala-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	go_home(t_shell *shell)
{
	t_list	*current;
	t_var	*var;

	current = shell->enviroment;
	while (current)
	{
		var = (t_var *)current->content;
		if (var && var->name && strcmp(var->name, "HOME") == 0)
		{
			chdir(var->value);
			return ;
		}
		current = current->next;
	}
}

int	get_directory(const char *path, char **parts, int idx)
{
	struct dirent	*entry;
	char			*folder;
	DIR				*dir;
	int				result;

	dir = opendir(path);
	path = ft_strjoin(path, "/");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR && strcmp(entry->d_name, parts[idx]) == 0)
		{
			folder = ft_strjoin(path, entry->d_name);
			if (parts[idx + 1] == NULL)
			{
				chdir(folder);
				return (closedir(dir), 1);
			}
			result = get_directory(folder, parts, idx + 1);
			return (closedir(dir), result);
		}
		entry = readdir(dir);
	}
	return (closedir(dir), 0);
}

void	go_folder(t_token *token)
{
	char	buff[PATH_MAX + 1];
	char	*cwd;
	char	**parts;

	cwd = getcwd(buff, PATH_MAX + 1);
	parts = ft_split(token->args[1], '/');
	if (parts == NULL || parts[0] == NULL)
	{
		printf("cd: invalid path\n");
		return ;
	}
	if (!get_directory(cwd, parts, 0))
		printf("cd: %s: No such file or patata\n", token->args[1]);
}
