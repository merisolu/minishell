/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:56:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/01/17 12:50:34 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Turns the given integer n into a string representation. */
char	*ft_itoa(int n)
{
	return (ft_itoa_base(n, 10));
}

/* Turns the given unsigned integer n into a string representation. */
char	*ft_itoa_uint(unsigned int n)
{
	return (ft_itoa_uint_base(n, 10));
}

/* Turns the given long long n into a string representation. */
char	*ft_itoa_llong(long long n)
{
	return (ft_itoa_llong_base(n, 10));
}

/* Turns the given unsigned long long n into a string representation. */
char	*ft_itoa_ullong(unsigned long long n)
{
	return (ft_itoa_ullong_base(n, 10));
}
