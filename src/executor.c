/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/06 15:57:35 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char *name, char *const *args, t_state *state)
{
	t_built_in	*built_in;
	char		temp_path[PATH_MAX];
	char		**paths;

	built_in = get_built_in(name);
	if (built_in)
		return (run_built_in(built_in, args, &state->env));
	else
	{
		paths = ft_strsplit(env_get("PATH", state->env), ':');
		if (!paths)
			return (print_error(ERR_MALLOC_FAIL, 1));
		bin_find(name, paths, temp_path);
		ft_free_null_array((void **)paths);
		if (temp_path[0])
		{
			ft_printf("Executing from path: %s\n", temp_path);
			return (bin_execute(temp_path, args, &state->env));
		}
		else
			return (print_error(ERR_COM_NOT_FOUND, RETURN_COMMAND_NOT_FOUND));
	}
}
