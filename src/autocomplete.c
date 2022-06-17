/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:07:51 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/17 11:01:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_execution_rights(char *path, char *name)
{
	int		result;
	char	*temp;

	ft_path_join(path, name, &temp);
	if (!temp)
		return (-1);
	result = access(temp, X_OK) == 0;
	free(temp);
	return (result);
}

/*
 * Searches the specific path for an executable file with a name matching
 * partial_name. The resulting file name will be put in *result. *result will
 * need to be freed once it's not used. It will be NULL if no match is found,
 * or on error.
 */
static int	search_path(char *path, char *partial_name, char **result)
{
	DIR				*dir;
	struct dirent	*entry;

	*result = NULL;
	dir = opendir(path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strnequ(partial_name, entry->d_name, ft_strlen(partial_name))
			&& check_execution_rights(path, entry->d_name) == 1)
		{
			*result = ft_strdup(entry->d_name);
			closedir(dir);
			if (!(*result))
				return (-1);
			return (1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

/*
 * Searches for a binary that at least partially matches state->input and is
 * located in any of the folders listed in the PATH environment variable.
 *
 * *result will be NULL if no match was found, or if an error has occured.
 */
static void	search_from_paths(t_state *state, char **result)
{
	int		search_return_value;
	char	*trimmed_input;
	char	**paths;
	size_t	i;

	trimmed_input = ft_strtrim(state->input);
	paths = ft_strsplit(env_get("PATH", state->env), ':');
	if (!trimmed_input || !paths)
	{
		print_error(ERR_MALLOC_FAIL, -1);
		free(trimmed_input);
		ft_free_null_array((void **)paths);
		return ;
	}
	i = 0;
	search_return_value = 0;
	while (paths[i] && search_return_value == 0)
	{
		search_return_value = search_path(paths[i], trimmed_input, result);
		if (search_return_value == -1)
			print_error(ERR_MALLOC_FAIL, -1);
		i++;
	}
	free(trimmed_input);
	ft_free_null_array((void **)paths);
}

/*
 * Attempts to autocomplete a partical binary name in state->input. If a match
 * is found, the partial name will be replaced with the full name.
 */
void	autocomplete(t_state *state)
{
	char	*temp;

	if (ft_strlen(state->input) == 0)
		return ;
	temp = search_for_built_in(state->input);
	if (!temp)
		search_from_paths(state, &temp);
	if (temp)
	{
		free(state->input);
		state->input = temp;
		state->cursor = ft_strlen(PROMPT) + ft_strlen(state->input);
	}
	return ;
}
