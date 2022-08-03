/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/03 13:37:16 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path_validity(char *path)
{
	if (ft_is_dir(path))
		return (print_named_error(path, ERR_IS_DIR, RETURN_NO_ACCESS));
	else if (path[ft_strlen(path) - 1] == '/')
		return (print_named_error(path, ERR_IS_NOT_DIR, RETURN_NO_ACCESS));
	else if (!ft_path_has_valid_end(path))
		return (print_named_error(
				path, ERR_NO_SUCH_FILE_OR_DIR, RETURN_COMMAND_NOT_FOUND)
		);
	return (0);
}

int	execute(char *const *args, t_state *state)
{
	t_cmd	*built_in;
	char	*path;
	int		return_value;

	if (!args || ft_strisempty(args[0]) || !env_set("_", args[0], &state->env))
		return (print_error(ERR_MALLOC_FAIL, 1));
	built_in = get_built_in(args[0]);
	if (built_in)
		return (run_built_in(built_in, args, state));
	if (ft_strchr(args[0], '/') || (args[0][0] == '.'))
	{
		return_value = check_path_validity(args[0]);
		if (return_value != 0)
			return (return_value);
		return (bin_execute(args[0], (char **)args, state->env, 1));
	}
	else if (bin_env_find(args[0], state->env, &path) == 0)
		return (print_named_error(
				args[0], ERR_COM_NOT_FOUND, RETURN_COMMAND_NOT_FOUND
			));
	return_value = env_set("_", path, &(state->env));
	if (return_value)
		return_value = bin_execute(path, (char **)args, state->env, 1);
	free(path);
	return (return_value);
}
