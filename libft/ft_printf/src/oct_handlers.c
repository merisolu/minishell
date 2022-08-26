/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oct_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:58:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/26 14:45:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	oct_writer(unsigned long long value, t_flags f)
{
	char		*str;
	int			len;

	str = ft_itoa_ullong_base(value, 8);
	if (!str)
		return (0);
	len = ft_strlen_int(str);
	if (f.precision == 0 && value == 0)
		len = 0;
	len += (f.hash && (value != 0 || (f.precision == 0 && value == 0)));
	if (!f.minus && !f.zero)
		insert_width(f, ft_max(f.precision, len));
	if (f.hash && (value != 0 || f.precision == 0))
		ft_putchar('0');
	if (!f.minus && f.zero)
		insert_width(f, ft_max(f.precision, len));
	insert_precision(f, len);
	if (!(f.precision == 0 && value == 0))
		ft_putstr(str);
	free(str);
	if (f.minus)
		insert_width(f, ft_max(len, f.precision));
	if (f.width)
		return (ft_max(len, ft_max(f.width, f.precision)));
	return (ft_max(len, f.precision));
}

int	oct_handler(va_list args, t_flags flags)
{
	if (ft_strequ(flags.length, "h"))
		return (oct_writer((unsigned short) va_arg(args, int), flags));
	if (ft_strequ(flags.length, "hh"))
		return (oct_writer((unsigned char) va_arg(args, int), flags));
	if (ft_strequ(flags.length, "l"))
		return (oct_writer(va_arg(args, unsigned long), flags));
	if (ft_strequ(flags.length, "ll"))
		return (oct_writer(va_arg(args, unsigned long long), flags));
	return (oct_writer(va_arg(args, unsigned int), flags));
}
