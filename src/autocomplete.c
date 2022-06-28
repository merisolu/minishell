/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:07:51 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/28 15:37:45 by jumanner         ###   ########.fr       */
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
	result = (access(temp, X_OK) == 0);
	free(temp);
	return (result);
}

static int	check_match_is_file(char *path, char *name)
{
	int		result;
	char	*temp;

	ft_path_join(path, name, &temp);
	if (!temp)
		return (print_error(ERR_MALLOC_FAIL, 0));
	result = (ft_is_file(temp) || ft_points_to_file(temp));
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
			&& check_execution_rights(path, entry->d_name) == 1
			&& check_match_is_file(path, entry->d_name) == 1)
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
 * Searches for a binary that at least partially matches the given input and is
 * located in any of the folders listed in the PATH environment variable.
 *
 * *result will be NULL if no match was found, or if an error has occured.
 */
static void	search_from_paths(char *const *env, char *input, char **result)
{
	int		search_return_value;
	char	**paths;
	size_t	i;

	paths = ft_strsplit(env_get("PATH", env), ':');
	if (!paths)
	{
		print_error(ERR_MALLOC_FAIL, -1);
		ft_free_null_array((void **)paths);
		return ;
	}
	i = 0;
	search_return_value = 0;
	while (paths[i] && search_return_value == 0)
	{
		search_return_value = search_path(paths[i], input, result);
		if (search_return_value == -1)
			print_error(ERR_MALLOC_FAIL, -1);
		i++;
	}
	ft_free_null_array((void **)paths);
}

/*
 * Attempts to autocomplete a partical binary name in state->input. If a match
 * is found, the partial name will be replaced with the full name.
 */
void	autocomplete(t_state *state)
{
	char	*trimmed_input;
	char	*temp;

	if (ft_strlen(state->input) == 0)
		return ;
	trimmed_input = ft_strtrim(state->input);
	if (ft_strlen(trimmed_input) == 0)
	{
		if (!trimmed_input)
			print_error(ERR_MALLOC_FAIL, 0);
		free(trimmed_input);
		return ;
	}
	temp = search_for_built_in(trimmed_input);
	if (!temp)
		search_from_paths(state->env, trimmed_input, &temp);
	if (temp)
	{
		free(state->input);
		state->input = temp;
		state->cursor = ft_strlen(PROMPT) + ft_strlen(state->input);
	}
	free(trimmed_input);
}
