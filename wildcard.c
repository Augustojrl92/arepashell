/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/01/28 23:11:21 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

char **ft_remove_index_sarray(char **arr, int index)
{
    int len = 0;
    if (!arr)
        return (NULL);
    while (arr[len])
        len++;
    if (index < 0 || index >= len)
        return (arr);

    // liberar si quieres la string actual
    free(arr[index]);
    // Mover el resto
    while (index < len - 1)
    {
        arr[index] = arr[index + 1];
        index++;
    }
    arr[index] = NULL; // cierra el hueco final

    return (arr);
}

char **ft_insert_sarray(char **arr, char **insert, int index)
{
    int len_arr = 0;
    int len_ins = 0;
    char **new_arr;
    int i, j;

    if (!arr)
        return (NULL);
    while (arr[len_arr])
        len_arr++;
    while (insert && insert[len_ins])
        len_ins++;
    if (index < 0)
        index = 0;
    if (index > len_arr)
        index = len_arr;
    new_arr = malloc(sizeof(char *) * (len_arr + len_ins + 1));
    if (!new_arr)
        return (arr); // si falla, devolvemos el viejo
    i = 0;
    while (i < index)
    {
        new_arr[i] = arr[i];
        i++;
    }
    j = 0;
    while (j < len_ins)
    {
        new_arr[i + j] = ft_strdup(insert[j]);
        j++;
    }
    while (arr[index])
    {
        new_arr[i + j] = arr[index];
        index++;
        j++;
    }
    new_arr[i + j] = NULL;
    free(arr);
    return (new_arr);
}

static int match_pattern(const char *filename, const char *pattern)
{
    const char *star = ft_strchr(pattern, '*');
    
    if (!star)
        return (ft_strcmp(filename, pattern) == 0);
    char *prefix = ft_substr(pattern, 0, star - pattern);
    char *suffix = ft_strdup(star + 1);
    if (ft_strncmp(filename, prefix, ft_strlen(prefix)) != 0)
    {
        free(prefix);
        free(suffix);
        return (0);
    }
    size_t filename_len = ft_strlen(filename);
    size_t suffix_len   = ft_strlen(suffix);
    if (filename_len < suffix_len)
    {
        free(prefix);
        free(suffix);
        return (0);
    }
    if (ft_strcmp(filename + (filename_len - suffix_len), suffix) != 0)
    {
        free(prefix);
        free(suffix);
        return (0);
    }
    free(prefix);
    free(suffix);
    return (1);
}

char **expand_wildcard_pattern(const char *pattern)
{
    DIR           *dir;
    struct dirent *entry;
    char         **matches = NULL;
    
    dir = opendir(".");
    if (!dir)
        return (NULL);

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.' && pattern[0] != '.')
            continue;
        if (match_pattern(entry->d_name, pattern))
        {
            matches = ft_add_to_sarray(matches, entry->d_name);
        }
    }
    closedir(dir);
    return (matches);
}

void expand_wildcards_in_args(t_token *token)
{
    int i = 0;

    if (!token->args)
        return;

    while (token->args[i])
    {
        if (!ft_strchr(token->args[i], '*'))
        {
            i++;
            continue;
        }
        char **matches = expand_wildcard_pattern(token->args[i]);
        if (!matches || !matches[0])
        {
            ft_free_sarray(matches);
            i++;
            continue;
        }
        token->args = ft_remove_index_sarray(token->args, i);
        token->args = ft_insert_sarray(token->args, matches, i);
        ft_free_sarray(matches);
    }
}

void expand_wildcards_in_outfiles(t_token *token)
{
    int i = 0;

    if (!token->outfiles)
        return;

    while (token->outfiles[i])
    {
        if (!ft_strchr(token->outfiles[i], '*'))
        {
            i++;
            continue;
        }
        char **matches = expand_wildcard_pattern(token->outfiles[i]);
        if (!matches || !matches[0])
        {
            ft_free_sarray(matches);
            i++;
            continue;
        }
        token->outfiles = ft_remove_index_sarray(token->outfiles, i);
        token->outfiles = ft_insert_sarray(token->outfiles, matches, i);
        ft_free_sarray(matches);
    }
}

