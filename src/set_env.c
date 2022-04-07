/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:04:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/07 13:06:39 by jumanner         ###   ########.fr       */
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
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (print_error("Variable name must begin with a letter.", 1));
	value = args[2];
	return (!env_set(name, value, env));
}
