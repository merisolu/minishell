/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/30 12:00:07 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path_validity(char *path)
{
	if (ft_is_dir(path))
		return (print_named_error(path, ERR_IS_DIR, 0));
	else if (path[ft_strlen(path) - 1] == '/')
		return (print_named_error(path, ERR_IS_NOT_DIR, 0));
	else if (!ft_path_has_valid_end(path))
		return (print_named_error(path, ERR_NO_SUCH_FILE_OR_DIR, 0));
	return (1);
}

int	execute(char *name, char *const *args, t_state *state)
{
	t_cmd	*built_in;
	char	*path;
	int		return_value;

	built_in = get_built_in(name);
	if (built_in)
		return (run_built_in(built_in, args, state));
	if (ft_strchr(name, '/'))
	{
		if (!check_path_validity(name))
			return (1);
		return (bin_execute(name, (char **)args, state->env, state));
	}
	else if (!bin_env_find(name, state->env, &path))
		return (
			print_named_error(
				name, ERR_COM_NOT_FOUND, RETURN_COMMAND_NOT_FOUND
			)
		);
	return_value = bin_execute(path, (char **)args, state->env, state);
	free(path);
	return (return_value);
}
