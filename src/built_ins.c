/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:18:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/10 15:16:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_built_in(const char *name)
{
	size_t						i;
	const static t_cmd_dispatch	dispatch_table[] = {
	{"cd", &cmd_cd},
	{"echo", &cmd_echo},
	{"env", &cmd_env},
	{"setenv", &cmd_setenv},
	{"unsetenv", &cmd_unsetenv},
	{"exit", &cmd_exit},
	{"", NULL}
	};

	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strequ(dispatch_table[i].name, name))
			return (dispatch_table[i].run);
		i++;
	}
	return (NULL);
}

int	run_built_in(t_cmd cmd, char *const *args, t_state *state)
{
	int	return_value;

	return_value = cmd(args, state);
	set_return_value(return_value, state);
	return (return_value);
}
