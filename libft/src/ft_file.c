/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:11:34 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/06 12:20:36 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns true if the given path is a regular file. False otherwise.
 */
int	ft_is_file(const char *path)
{
	struct stat		temp;

	if (lstat(path, &temp) == -1)
		return (0);
	else if ((temp.st_mode & S_IFMT) == S_IFREG)
		return (1);
	return (0);
}

/*
 * Returns true if the given path points to a regular file. False otherwise.
 */
int	ft_points_to_file(const char *path)
{
	struct stat		temp;

	if (stat(path, &temp) == -1)
		return (0);
	else if ((temp.st_mode & S_IFMT) == S_IFREG)
		return (1);
	return (0);
}
