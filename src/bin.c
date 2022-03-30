/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:29:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 13:20:09 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Attempts to find the given binary from all available paths. If the binary was
 * found its path will be stored in result. If nothing was found, result
 * will be empty.
 */
void	bin_find(const char *name, t_state *state, char result[PATH_MAX])
{
	size_t	i;
	char	path_buffer[PATH_MAX];

	ft_bzero(result, PATH_MAX);
	i = 0;
	while ((*state).paths[i])
	{
		ft_path_join((*state).paths[i], name, path_buffer);
		if (ft_path_has_valid_end(path_buffer))
		{
			ft_strcpy(result, path_buffer);
			break ;
		}
		i++;
	}
}
