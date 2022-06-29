/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:04:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/29 11:19:50 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_setenv(char *const *args, t_state *state)
{
	char	*name;
	char	*value;

	name = args[1];
	if (!name)
	{
		env_print_all(state->env);
		return (0);
	}
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (print_named_error(
				"setenv", "Variable name must begin with a letter.", 1
			));
	value = args[2];
	if (!value)
	{
		value = ft_strchr(name, '=');
		if (!value)
			return (0);
		else
			value += 1;
		name[ft_dstchr(name, '=', ft_strlen(name))] = '\0';
	}
	return (!env_set(name, value, &(state->env)));
}
