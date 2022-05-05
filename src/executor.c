/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/05 15:24:04 by jumanner         ###   ########.fr       */
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
	t_built_in	*built_in;
	char		*temp_path;

	built_in = get_built_in(name);
	if (built_in)
		return (run_built_in(built_in, args, state));
	else
	{
		if (ft_strchr(name, '/'))
		{
			temp_path = ft_strdup(name);
			if (!temp_path)
				return (print_error(ERR_MALLOC_FAIL, 1));
			if (!check_path_validity(temp_path))
				return (1);
			return (bin_execute(temp_path, (char **)args, &(state->env)));
		}
		else if (!bin_env_find(name, state->env, &temp_path))
			return (
				print_named_error(
					name, ERR_COM_NOT_FOUND, RETURN_COMMAND_NOT_FOUND
				)
			);
		return (bin_execute(temp_path, (char **)args, &(state->env)));
	}
}
