/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharn_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:18:22 by jumanner          #+#    #+#             */
/*   Updated: 2022/01/18 13:35:23 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Writes the given character n times to the given file descriptor. */
void	ft_putcharn_fd(char c, int n, int fd)
{
	while (n > 0)
	{
		write(fd, &c, 1);
		n--;
	}	
}
