/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   written_chars_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:58:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/04 12:10:35 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	written_chars_handler(va_list args, int written_chars)
{
	int	*result;

	result = va_arg(args, int *);
	*result = written_chars;
	return (0);
}
