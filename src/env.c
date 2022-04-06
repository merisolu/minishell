/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:39:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/06 12:59:59 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Returns a pointer to an environment variable string with the given name
 * in the environment variable array. Returns NULL if nothing was found.
 */
static char	**env_get_pointer(const char *name, char *const *env)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (env[i])
	{
		temp = ft_strnstr(env[i], name, ft_strlen(name));
		if (temp)
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
 * Sets an environment variable to the given value.
 *
 * If there is no existing variable with the same name, the variable is added
 * to the end of the list. If there already is a variable with the same name,
 * the value of it is updated.
 *
 * Returns one on success, zero otherwise.
 */
int	env_set(const char *name, const char *value, char *const **env)
{
	size_t	new_size;
	char	**destination_pointer;
	char	*new;

	destination_pointer = env_get_pointer(name, *env);
	if (!destination_pointer)
	{
		new_size = ft_null_array_len((void **)*env) + 1;
		if (!ft_resize_null_array((void ***)(env), new_size))
			return (print_error(ERR_MALLOC_FAIL, 0));
		destination_pointer = (char **)*env + new_size - 1;
	}
	new = ft_strnew(ft_strlen(name) + 1 + ft_strlen(value));
	if (!new)
		return (print_error(ERR_MALLOC_FAIL, 0));
	ft_strcpy(new, name);
	new[ft_strlen(name)] = '=';
	if (value)
		ft_strcpy(new + ft_strlen(name) + 1, value);
	free(*destination_pointer);
	*destination_pointer = new;
	return (1);
}

/*
 * Removes an environment variable, if it is set. If the variable is not set,
 * nothing is done and one is returned.
 *
 * Returns one on success, zero otherwise.
 */
int	env_unset(const char *name, char *const **env)
{
	char	**removeable;

	removeable = env_get_pointer(name, *env);
	if (removeable)
	{
		if (!ft_remove_from_null_array((void ***)env, (void *)(*removeable)))
			return (print_error(ERR_MALLOC_FAIL, 0));
	}
	return (1);
}

/*
 * Prints all environment variables.
 */
void	env_print_all(char *const *env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}
