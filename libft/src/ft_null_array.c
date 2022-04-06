/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:52:47 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/06 12:16:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/*
 * Copies the null terminated array from src to dst. dst needs to have
 * enough space for the copy.
 * 
 * If the cpy function is NULL, the each pointer in the array is copied.
 */
void	ft_copy_null_array(void **dst, void **src, void *(*cpy)(void *))
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (cpy)
			dst[i] = cpy(src[i]);
		else
			dst[i] = src[i];
		i++;
	}
}

/*
 * Duplicates the null terminated array src, and puts the result to the
 * address that result points to.
 * 
 * If the cpy function is NULL, the each pointer in the array is copied.
 * 
 * One will be returned on success. Zero otherwise.
 */
int	ft_dup_null_array(void **src, void ***result, void *(*cpy)(void *))
{
	size_t	size;

	size = ft_null_array_len(src);
	*result = (void **)ft_memalloc(sizeof(void *) * (size + 1));
	if (!(*result))
		return (0);
	ft_copy_null_array(*result, src, cpy);
	return (1);
}

/*
 * Resizes the given null terminated array to the given size and frees the
 * original array pointer.
 * 
 * One will be returned on success. Zero otherwise.
 */
int	ft_resize_null_array(void ***array, size_t size)
{
	void	**result;

	result = (void **)ft_memalloc(sizeof(void *) * (size + 1));
	if (!result)
		return (0);
	ft_copy_null_array(result, *array, NULL);
	free(*array);
	*array = result;
	return (1);
}
