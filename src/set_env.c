/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:04:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/01 16:29:46 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env(char *const *args, char *const **env)
{
	char	*name;
	char	*value;

	(void)env;
	name = args[1];
	if (!name)
	{
		env_print_all(*env);
		return (0);
	}
	value = args[2];
	env_set(name, value, env);
	return (0);
}
