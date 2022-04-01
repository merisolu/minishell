/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:52:47 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/01 15:55:57 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc.h"

/* 
 * Frees each element of the given null-terminated array, then the pointer to
 * the array. Returns NULL when done.
 */
void	*ft_free_null_array(void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

/*
 * Returns the length of a null-terminated array.
 */
size_t	ft_null_array_len(void **array)
{
	size_t	result;

	if (!array || !(*array))
		return (0);
	result = 0;
	while (array[result])
		result++;
	return (result);
}
