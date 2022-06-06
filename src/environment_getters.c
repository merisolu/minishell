/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:52:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/06 11:18:05 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Returns a pointer to an environment variable string with the given name
 * in the environment variable array. Returns NULL if nothing was found.
 */
char	**env_get_pointer(const char *name, char *const *env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, \
			ft_dstchr(env[i], '=', ft_strlen(env[i]))) == 0)
			return ((char **)env + i);
		i++;
	}
	return (NULL);
}

/*
 * Attempts to return the value of the environment variable matching the given
 * name. Returns NULL if nothing was found.
 */
char	*env_get(const char *name, char *const *env)
{
	char	**temp;

	temp = env_get_pointer(name, env);
	if (temp)
		return (ft_strchr(*temp, '=') + 1);
	return (NULL);
}

/*
 * Attempts to return the value of the environment variable matching the given
 * name. Returns on_fail if nothing was found.
 */
char	*env_get_or(char *name, char *on_fail, char *const *env)
{
	char	*temp;

	temp = env_get(name, env);
	if (temp)
		return (temp);
	return (on_fail);
}
