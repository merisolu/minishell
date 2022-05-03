/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:04:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/03 13:36:53 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_setenv(char *const *args, t_state *state)
{
	char	*name;
	char	*value;

	(void)state;
	name = args[1];
	if (!name)
	{
		env_print_all(state->env);
		return (0);
	}
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (print_error("Variable name must begin with a letter.", 1));
	value = args[2];
	return (!env_set(name, value, &(state->env)));
}
