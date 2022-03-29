/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_validity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:21:28 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/18 16:32:38 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns true if the path exists.
 */
int	ft_path_has_valid_end(char *path)
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
int	ft_path_has_valid_link(char *path)
{
	struct stat		temp;

	if (stat(path, &temp) != -1)
		return (1);
	return (0);
}
