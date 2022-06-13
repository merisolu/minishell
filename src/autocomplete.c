/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:07:51 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/13 11:35:01 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: This fails when the string begins with whitespace
char	*find_from_path(char *path, char *partial_name)
{
	char			*result;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strnequ(partial_name, entry->d_name, ft_strlen(partial_name)))
		{
			result = ft_strdup(entry->d_name); // TODO: Malloc check?
			closedir(dir);
			return (result);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

char	*find_from_paths(t_state *state)
{
	char	*result;
	char	**paths;
	size_t	i;

	if (!env_get("PATH", state->env))
		return (NULL);
	paths = ft_strsplit(env_get("PATH", state->env), ':');
	if (!paths)
	{
		print_error(ERR_MALLOC_FAIL, 0);
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		result = find_from_path(paths[i], state->input);
		if (result)
		{
			ft_free_null_array((void **)paths);
			return (result);
		}
		i++;
	}
	return (ft_free_null_array((void **)paths));
}

// TODO: Return errors.
/*
 * Attempts to autocomplete a partical binary name in state->input. If a match
 * is found, the partial name will be replaced with the full name.
 */
void	autocomplete(t_state *state)
{
	char	*temp;

	if (ft_strlen(state->input) == 0)
		return;
	temp = find_from_paths(state);
	if (temp)
	{
		free(state->input);
		state->input = temp;
		state->cursor = ft_strlen(PROMPT) + ft_strlen(state->input);
	}
	print_state(state, 0);
	return;
}
