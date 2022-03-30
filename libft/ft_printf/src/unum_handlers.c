/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unum_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:58:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/03 14:47:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_cap(t_flags f, int sign, int len, int end)
{
	int	space;

	space = 0;
	if (((f.minus && end) || (!f.minus && !end)) && f.precision != -1)
	{
		space = f.width - ft_max(f.precision, len) + (sign == -1);
		if (sign >= 0)
			space -= ((f.plus || f.space) && sign >= 0);
		else
			space -= 1;
	}
	else if (((f.minus && end) || (!f.minus && !end)) && !f.zero)
		space = f.width - len;
	ft_putcharn(' ', space);
}

static int	unum_writer(unsigned long long n, t_flags f)
{
	int	len;

	len = ft_getnumlen_ullong(n);
	if (f.precision == 0 && n == 0)
		len = 0;
	else if (f.zero && f.width > 0 && f.precision == -1)
		len = ft_max(f.width, len);
	else
		len = ft_max(f.precision, len);
	print_cap(f, 1, len, 0);
	ft_putnbrn_ullong(n, len);
	print_cap(f, 1, len, 1);
	if (f.width)
		return (ft_max(len, ft_max(f.width, f.precision)));
	return (len);
}

int	unum_handler(va_list args, t_flags flags)
{
	if (ft_strequ(flags.length, "h"))
		return (unum_writer((unsigned short) va_arg(args, int), flags));
	if (ft_strequ(flags.length, "hh"))
		return (unum_writer((unsigned char) va_arg(args, int), flags));
	if (ft_strequ(flags.length, "l"))
		return (unum_writer(va_arg(args, unsigned long), flags));
	if (ft_strequ(flags.length, "ll"))
		return (unum_writer(va_arg(args, unsigned long long), flags));
	if (ft_strequ(flags.length, "j"))
		return (unum_writer(va_arg(args, uintmax_t), flags));
	if (ft_strequ(flags.length, "z"))
		return (unum_writer(va_arg(args, size_t), flags));
	return (unum_writer(va_arg(args, unsigned int), flags));
}
