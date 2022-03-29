/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:48:50 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/25 14:18:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the distance to the byte c in the string s. Returns -1 if nothing
 * was found in the range. */
size_t	ft_dstchr(char *s, char c, size_t max)
{
	size_t	result;

	result = 0;
	while (result < max && s[result] != c)
		result++;
	if (s[result] == c)
		return (result);
	return (-1);
}
