/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:52:47 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/13 14:29:32 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies the null terminated array from src to dst. dst needs to have
 * enough space for the copy.
 * 
 * If the cpy function is NULL, the each pointer in the array is copied.
 * 
 * One will be returned on a successful copy. Zero otherwise.
 */
int	ft_copy_null_array(void **dst, void **src, void *(*cpy)(void *))
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (cpy)
		{
			dst[i] = cpy(src[i]);
			if (!((src[i] && dst[i]) || (!(src[i]) && !(dst[i]))))
				return (0);
		}
		else
			dst[i] = src[i];
		i++;
	}
	return (1);
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
	return (ft_copy_null_array(*result, src, cpy));
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

/*
 * Increases the given null terminated array's size by one and adds
 * the provided element to the newly-created slot.
 *
 * One will be returned on success. Zero otherwise.
 */
int	ft_add_to_null_array(void ***array, void *new)
{
	size_t	new_len;

	new_len = ft_null_array_len(*array) + 1;
	if (!ft_resize_null_array(array, new_len))
		return (0);
	(*array)[new_len - 1] = new;
	return (1);
}

/*
 * Creates a new null terminated array using the given array as a base,
 * but with the specified removeable element removed.
 *
 * One will be returned on success. Zero otherwise.
 */
int	ft_remove_from_null_array(void ***array, void *removeable)
{
	void	**result;
	size_t	src_i;
	size_t	dst_i;

	result = (void **)ft_memalloc(sizeof(void *) * (ft_null_array_len(*array)));
	if (!result)
		return (0);
	src_i = 0;
	dst_i = 0;
	while ((*array)[src_i])
	{
		if ((*array)[src_i] == removeable)
		{
			src_i++;
			continue ;
		}
		result[dst_i] = (*array)[src_i];
		src_i++;
		dst_i++;
	}
	free(removeable);
	free(*array);
	(*array) = result;
	return (1);
}
