/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:48:57 by layala-s          #+#    #+#             */
/*   Updated: 2025/02/16 21:12:06 by aurodrig         ###   ########.fr       */
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
		if (var && var->name && ft_strcmp(var->name, "HOME") == 0)
		{
			chdir(var->value);
			return ;
		}
		current = current->next;
	}
}

char	*find_subdirectory(DIR *dir, const char *path, const char *subdir_name)
{
	struct dirent	*entry;
	char			*full_path;

	full_path = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR && \
		ft_strcmp(entry->d_name, subdir_name) == 0)
		{
			full_path = ft_strjoin(path, entry->d_name);
			break ;
		}
		entry = readdir(dir);
	}
	return (full_path);
}

int	get_directory(char *path, char **parts, int idx)
{
	DIR		*dir;
	char	*temp_path;
	char	*folder;
	int		result;

	dir = opendir(path);
	if (!dir)
		return (0);
	if (path)
		temp_path = ft_strjoin(path, "/");
	if (!temp_path)
		return (closedir(dir), 0);
	folder = find_subdirectory(dir, temp_path, parts[idx]);
	if (folder)
	{
		if (parts[idx + 1] == NULL)
		{
			chdir(folder);
			return (free(folder), free(temp_path), closedir(dir), 1);
		}
		result = get_directory(folder, parts, idx + 1);
		return (free(folder), free(temp_path), closedir(dir), result);
	}
	return (free(temp_path), closedir(dir), (0));
}

void	go_folder(t_token *token, t_shell *shell)
{
	char	buff[PATH_MAX + 1];
	char	*cwd;
	char	**parts;
	int		i;

	i = 0;
	cwd = getcwd(buff, PATH_MAX + 1);
	parts = ft_split(token->args[1], '/');
	if (parts == NULL || parts[0] == NULL)
	{
		printf("cd: invalid path\n");
		while (parts[i])
			free(parts[i++]);
		free(parts);
		return ;
	}
	if (!get_directory(cwd, parts, 0))
		printf("cd: %s: No such file or directory\n", token->args[1]);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	shell->last_path = cwd;
}

int	check_dir(t_shell *shell)
{
	perror("cd: getcwd failed");
	if (shell->last_path)
		chdir(shell->last_path);
	else
		go_home(shell);
	return (1);
}
