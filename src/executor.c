/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/10 11:55:50 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path_validity(char *path)
{
	if (ft_is_dir(path))
	{
		free((void *)path);
		return (print_named_error(path, ERR_IS_DIR, 0));
	}
	else if (path[ft_strlen(path) - 1] == '/')
	{
		free((void *)path);
		return (print_named_error(path, ERR_IS_NOT_DIR, 0));
	}
	else if (!ft_path_has_valid_end(path))
	{
		free((void *)path);
		return (print_named_error(path, ERR_NO_SUCH_FILE_OR_DIR, 0));
	}
	return (1);
}

int	execute(char *name, char *const *args, t_state *state)
{
	t_cmd	*built_in;
	char	*path;

	built_in = get_built_in(name);
	if (built_in)
		return (run_built_in(built_in, args, state));
	else
	{
		if (ft_strchr(name, '/'))
		{
			path = ft_strdup(name);
			if (!path)
				return (print_error(ERR_MALLOC_FAIL, 1));
			if (!check_path_validity(path))
				return (1);
			return (bin_execute(path, (char **)args, state->env, state));
		}
		else if (!bin_env_find(name, state->env, &path))
			return (
				print_named_error(
					name, ERR_COM_NOT_FOUND, RETURN_COMMAND_NOT_FOUND
				)
			);
		return (bin_execute(path, (char **)args, state->env, state));
	}
}
