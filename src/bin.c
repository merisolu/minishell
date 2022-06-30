/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:29:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/30 12:01:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Attempts to find the given binary from all given paths, the local directory
 * if the name beings with "./", and the absolute path if the name begins with
 * a slash.
 *
 * If the binary was found its path will be stored in result. If nothing was
 * found, the result will be NULL.
 *
 * *result should be freed after it is no longer needed.
 */
void	bin_find(const char *name, char **paths, char **result)
{
	size_t	i;

	i = 0;
	if ((name[0] == '/' || ft_strnequ(name, "./", 2))
		&& ft_points_to_file(name))
	{
		*result = ft_strdup(name);
		return ;
	}
	while (paths[i])
	{
		ft_path_join(paths[i], name, result);
		if (ft_points_to_file(*result))
			return ;
		else
			ft_memdel((void **)result);
		i++;
	}
	*result = NULL;
}

/*
 * Attempts to find the given binary from all paths in the given environment,
 * or if an absolute path was passed directly from the given path.
 *
 * If the binary was found its path will be stored in result. If nothing was
 * found, the result will be empty.
 *
 * Returns one on success, zero on failure.
 */
int	bin_env_find(const char *name, char *const *env, char **result)
{
	char	**paths;

	if (!env_get("PATH", env))
	{
		*result = NULL;
		return (0);
	}
	paths = ft_strsplit(env_get("PATH", env), ':');
	if (!paths)
		return (print_error(ERR_MALLOC_FAIL, 0));
	bin_find(name, paths, result);
	ft_free_null_array((void **)paths);
	return (*result != NULL);
}

/*
 * Attempts to fork the current process, transform it into a new process
 * defined by the given path to a binary, and wait for its execution to finish.
 *
 * If fork or execve calls fail, an error message is printed to stderr.
 */
int	bin_execute(char *path, char **args, char *const *env, t_state *state)
{
	pid_t	process_pid;
	int		status;

	if (access(path, X_OK) == -1)
		return (print_named_error(
				(char *)path, ERR_NO_PERMISSION, RETURN_NO_PERMISSION
			));
	process_pid = fork();
	if (process_pid == 0)
	{
		if (execve(path, args, env) == -1)
			exit(print_error(ERR_CHILD_PROC_FAIL, 1));
	}
	else if (process_pid == -1)
		return (print_error(ERR_CHILD_PROC_FAIL, 1));
	waitpid(process_pid, &status, 0);
	set_return_value_from_status(status, state);
	return (0);
}
