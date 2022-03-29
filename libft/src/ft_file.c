/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:07:15 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/18 15:12:00 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns true if the given file/directory the path points to is hidden.
 */
int	ft_is_hidden(char *path)
{
	char	*name;

	name = ft_get_path_name_ptr(path);
	if (!name)
		return (0);
	return (name[0] == '.');
}
