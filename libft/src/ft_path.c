/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:02:51 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/31 16:35:26 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Joins two paths together, and puts the result into dst.
 */
void	ft_path_join(const char *a, const char *b, char dst[PATH_MAX + 1])
{
	size_t	i;

	ft_bzero(dst, PATH_MAX + 1);
	ft_strcpy(dst, a);
	i = ft_strlen(a);
	if (a[i - 1] != '/')
	{
		dst[ft_strlen(a)] = '/';
		i++;
	}
	ft_strcpy((dst + i), b);
}

/*
 * Returns a pointer to the last named section of the path.
 * Returns null on failure.
 */
char	*ft_get_path_name_ptr(const char *path)
{
	char	*result;

	if (!path)
		return (NULL);
	result = ft_strrchr(path, '/');
	if (!result)
		return ((char *)path);
	return (result + 1);
}

/*
 * Returns true if the given path is self (.) or parent (..);
 */
int	ft_path_is_self_or_parent(const char *path)
{
	char	*name;

	name = ft_get_path_name_ptr(path);
	return (ft_strequ(name, ".") || ft_strequ(name, "..")
		|| ft_strequ(name, "./.") || ft_strequ(name, "./.."));
}

/*
 * Returns true if the given file/directory the path points to is hidden.
 */
int	ft_is_hidden(const char *path)
{
	char	*name;

	name = ft_get_path_name_ptr(path);
	if (!name)
		return (0);
	return (name[0] == '.');
}

/*
 * Returns true if the given path is absolute.
 */
int	ft_path_is_absolute(const char *path)
{
	if (!path)
		return (0);
	return (path[0] == '/');
}
