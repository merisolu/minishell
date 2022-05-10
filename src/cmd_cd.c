/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:27:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/10 15:14:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_cd_error(char *name, char *message, int return_value)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (return_value);
}

static int	check_destination_errors(char *name, char *path)
{
	if (ft_points_to_file(path))
		return (print_cd_error(name, ERR_IS_NOT_DIR, 1));
	if (!ft_points_to_dir(path))
		return (print_cd_error(name, ERR_NO_SUCH_FILE_OR_DIR, 1));
	if (!ft_path_is_within_limits(path))
		return (print_cd_error(name, ERR_INVALID_PATH, 1));
	return (0);
}

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
			return (print_error(ERR_MALLOC_FAIL, 0));
	}
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (print_error(ERR_CANNOT_GET_CWD, 0));
		ft_path_join(path, target, result);
		free(path);
	}
	return (1);
}

int	cmd_cd(char *const *args, t_state *state)
{
	char	*target;
	char	*path;
	size_t	arg_count;
	int		return_value;

	arg_count = ft_null_array_len((void **)args);
	target = get_target(args, arg_count, state->env);
	if (!ft_path_is_within_limits(target))
		return (print_cd_error(target, ERR_INVALID_PATH, 1));
	if (!construct_path(target, &path))
		return (1);
	return_value = check_destination_errors(target, path);
	if (return_value != 0)
	{
		free(path);
		return (return_value);
	}
	if (env_get("PWD", state->env))
		env_set("OLDPWD", env_get("PWD", state->env), &(state->env));
	ft_normalize_path(path, &target);
	env_set("PWD", target, &(state->env));
	return_value = chdir(target);
	free(target);
	free(path);
	return (return_value);
}
