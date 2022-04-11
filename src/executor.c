/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/07 15:05:36 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char *name, char *const *args, t_state *state)
{
	t_built_in	*built_in;
	char		temp_path[PATH_MAX];

	built_in = get_built_in(name);
	if (built_in)
		return (run_built_in(built_in, args, &(state->env)));
	else
	{
		if (!bin_env_find(name, state->env, temp_path))
			return (1);
		if (temp_path[0])
			return (bin_execute(temp_path, (char **)args, &(state->env)));
		else
			return (print_error(ERR_COM_NOT_FOUND, RETURN_COMMAND_NOT_FOUND));
	}
}
