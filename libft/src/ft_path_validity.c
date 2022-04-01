/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_validity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:21:28 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/01 14:29:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns true if the path exists.
 */
int	ft_path_has_valid_end(const char *path)
{
	struct stat		temp;

	if (lstat(path, &temp) != -1)
		return (1);
	return (0);
}

/*
 * Returns true if the path points to a link that has a valid destination or
 * if the file is not a link, returns true if the file exists.
 */
int	ft_path_has_valid_link(const char *path)
{
	struct stat		temp;

	if (stat(path, &temp) != -1)
		return (1);
	return (0);
}

/*
 * Returns true if the given path as a whole does not exceed PATH_MAX, and
 * each individual name on the path does not exceed NAME_MAX.
 */
int	ft_path_is_within_limits(const char *path)
{
	char	**names;
	size_t	i;

	if (ft_strlen(path) >= PATH_MAX)
		return (0);
	names = ft_strsplit(path, '/');
	if (!names)
		return (0);
	i = 0;
	while (names[i])
	{
		if (ft_strlen(names[i]) >= NAME_MAX)
		{
			ft_free_null_array((void **)names);
			return (0);
		}
		i++;
	}
	ft_free_null_array((void **)names);
	return (1);
}
