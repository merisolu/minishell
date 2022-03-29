/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatchers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:23:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/04 12:06:01 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	text_dispatch(t_flags *flags, char character, va_list args)
{
	if (character == 'c')
		return (char_handler(args, *flags));
	if (character == 's')
		return (string_handler(args, *flags));
	if (character == 'p')
		return (pointer_handler(args, *flags));
	if (character == '%')
		return (percentage_handler(args, *flags));
	return (-1);
}

int	numeric_dispatch(t_flags *flags, char character, va_list args)
{
	if (character == 'i' || character == 'd')
		return (num_handler(args, *flags));
	if (character == 'u')
		return (unum_handler(args, *flags));
	if (character == 'U')
	{
		(*flags).length = "l";
		return (unum_handler(args, *flags));
	}
	if (character == 'f')
		return (float_handler(args, *flags));
	if (character == 'x')
		return (hex_handler(args, *flags, ft_strtolower));
	if (character == 'X')
		return (hex_handler(args, *flags, ft_strtoupper));
	if (character == 'o')
		return (oct_handler(args, *flags));
	return (-1);
}

int	custom_dispatch(t_flags *flags, char character, va_list args, int chars)
{
	if (character == 'b')
		return (bin_handler(args, *flags, ft_strtolower));
	if (character == 'B')
		return (bin_handler(args, *flags, ft_strtoupper));
	if (character == 'q')
		return (b36_handler(args, *flags, ft_strtolower));
	if (character == 'Q')
		return (b36_handler(args, *flags, ft_strtoupper));
	if (character == 'n')
		return (written_chars_handler(args, chars));
	return (-1);
}
