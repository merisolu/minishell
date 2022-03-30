/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:39:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 16:30:30 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Attempts to find an environment variable matching the given name.
 * Returns NULL if not found.
 */
char	*env_get(const char *name, char *const *env)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (env[i])
	{
		temp = ft_strnstr(env[i], name, ft_strlen(name));
		if (temp)
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}
