/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:27:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/11 12:20:40 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target(char *const *args, size_t count, char *const *env)
{
	if (count == 1)
		return (env_get("HOME", env));
	else
	{
		if (ft_strequ(args[1], "-"))
			return (env_get("OLDPWD", env));
	}
	return (args[1]);
}

static int	construct_path(char *target, char **result)
{
	char	*path;

	if (ft_path_is_absolute(target))
	{
		*result = ft_strdup(target);
		if (!(*result))
			return (print_error(ERR_MALLOC_FAIL, 1));
	}
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (print_error(ERR_CANNOT_GET_CWD, 1));
		ft_path_join(path, target, result);
	}
	return (0);
}

int	cmd_cd(char *const *args, char *const **env)
{
	char	*target;
	char	*path;
	size_t	arg_count;
	int		return_code;

	arg_count = ft_null_array_len((void **)args);
	if (arg_count > 2)
		return (print_error(ERR_TOO_MANY_ARGS, 1));
	target = get_target(args, arg_count, *env);
	if (!target)
		return (0);
	if (!ft_path_is_within_limits(target))
		return (print_error(ERR_PATH_TOO_LONG, 1));
	return_code = construct_path(target, &path);
	if (return_code != 0)
		return (return_code);
	if (!ft_points_to_dir(path))
		return (print_error(ERR_NO_SUCH_FILE_OR_DIR, 1));
	if (!ft_path_is_within_limits(path))
		return (print_error(ERR_PATH_TOO_LONG, 1));
	return (ft_abs(chdir(path)));
}
