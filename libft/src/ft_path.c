/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:02:51 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/23 12:01:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Joins two paths together, and puts the result into dst.
 */
void	ft_path_join(char *path1, char *path2, char dst[PATH_MAX + 1])
{
	size_t	i;

	ft_bzero(dst, PATH_MAX + 1);
	ft_strcpy(dst, path1);
	i = ft_strlen(path1);
	if (path1[i - 1] != '/')
	{
		dst[ft_strlen(path1)] = '/';
		i++;
	}
	ft_strcpy((dst + i), path2);
}

/*
 * Returns a pointer to the last named section of the path.
 * Returns null on failure.
 */
char	*ft_get_path_name_ptr(char *path)
{
	char	*result;

	if (!path)
		return (NULL);
	result = ft_strrchr(path, '/');
	if (!result)
		return (path);
	return (result + 1);
}

/*
 * Returns true if the given path is self (.) or parent (..);
 */
int	ft_path_is_self_or_parent(char *path)
{
	char	*name;

	name = ft_get_path_name_ptr(path);
	return (ft_strequ(name, ".") || ft_strequ(name, "..")
		|| ft_strequ(name, "./.") || ft_strequ(name, "./.."));
}
