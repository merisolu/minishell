/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/31 16:10:59 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char *name, char *const *args, t_state *state)
{
	t_built_in	*built_in;
	char		temp_path[PATH_MAX];

	built_in = get_built_in(name);
	if (built_in)
		return (run_built_in(built_in, args, state->env));
	else
	{
		bin_find(name, state, temp_path);
		if (temp_path[0])
		{
			ft_printf("Executing from path: %s\n", temp_path);
			return (bin_execute(temp_path, args, state->env));
		}
		else
			return (print_error(ERR_COM_NOT_FOUND, COMMAND_NOT_FOUND));
	}
}
