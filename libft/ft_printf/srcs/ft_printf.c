/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:25:19 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/17 11:51:04 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_format(t_flags *flags, char **cursor, va_list args)
{
	(*flags).minus = 0;
	(*flags).plus = 0;
	(*flags).space = 0;
	(*flags).hash = 0;
	(*flags).zero = 0;
	(*flags).width = 0;
	(*flags).precision = -1;
	(*flags).length = "";
	(*flags).start = *cursor;
	parse_flags(cursor, flags);
	parse_width(cursor, args, flags);
	parse_precision(cursor, args, flags);
	parse_length(cursor, flags);
}

static int	run_handlers(t_flags *flags, char **cursor, va_list args, int wc)
{
	int	result;

	result = text_dispatch(flags, **cursor, args);
	if (result == -1)
		result = numeric_dispatch(flags, **cursor, args);
	if (result == -1)
		result = custom_dispatch(flags, **cursor, args, wc);
	if (result == -1 && **cursor != '\0')
	{
		*cursor = (*flags).start - 1;
		ft_putchar(**cursor);
		return (1);
	}
	return (ft_max(result, 0));
}

static int	finalize_string(int has_color, int written_chars)
{
	if (has_color != 0)
		ft_putstr(COLOR_RESET);
	return (written_chars);
}

/* 
 * Format: %[flags][width][.precision][length]specifier
*/
static int	parse_string(char *cursor, va_list args)
{
	t_flags	flags;
	int		written_chars;
	int		has_color;

	has_color = 0;
	written_chars = 0;
	while (*cursor)
	{
		has_color += parse_color(&cursor);
		if (*cursor == '%')
		{
			cursor++;
			parse_format(&flags, &cursor, args);
			written_chars += run_handlers(&flags, &cursor, args, written_chars);
			if (!(*cursor))
				return (finalize_string(has_color, written_chars));
		}
		else if (*cursor)
		{
			ft_putchar(*cursor);
			written_chars++;
		}
		cursor++;
	}
	return (finalize_string(has_color, written_chars));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		written_chars;

	va_start(args, format);
	written_chars = parse_string((char *)format, args);
	va_end(args);
	return (written_chars);
}
