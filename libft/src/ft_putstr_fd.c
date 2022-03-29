/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:48:27 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:08:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Writes the given string to the given file descriptor using ft_putchar_fd. */
void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
