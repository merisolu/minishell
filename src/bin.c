/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:29:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/06 15:53:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Attempts to find the given binary from all given paths. If the binary was
 * found its path will be stored in result. If nothing was found, the result
 * will be empty.
 */
void	bin_find(const char *name, char **paths, char result[PATH_MAX])
{
	size_t	i;
	char	path_buffer[PATH_MAX];

	ft_bzero(result, PATH_MAX);
	i = 0;
	while (paths[i])
	{
		ft_path_join(paths[i], name, path_buffer);
		if (ft_points_to_file(path_buffer) && access(path_buffer, X_OK) == 0)
		{
			ft_strcpy(result, path_buffer);
			break ;
		}
		i++;
	}
}

// TODO: Handle return value.
/*
 * Attempts to fork the current process, transform it into a new process
 * defined by the given path to a binary, and wait for its execution to finish.
 * If fork or execve calls fail, an error message is printed to stderr.
 */
int	bin_execute(const char *path, char *const *args, char *const **env)
{
	pid_t	process_pid;

	process_pid = fork();
	if (process_pid == 0)
	{
		if (execve(path, args, *env) == -1)
			return (print_error(ERR_EXECVE_FAIL, 1));
	}
	else if (process_pid == -1)
		return (print_error(ERR_FORK_FAIL, 1));
	else
		wait(NULL);
	return (0);
}
