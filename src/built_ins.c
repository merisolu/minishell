/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:18:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/31 16:39:25 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_built_in	*get_built_in(const char *name)
{
	size_t								i;
	const static t_built_in_dispatch	dispatch_table[] = {
	{"cd", &cd},
	{"echo", &echo},
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

int	run_built_in(t_built_in com, char *const *args, char *const *env)
{
	return (com(args, env));
}
