/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:58:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/14 15:29:36 by jumanner         ###   ########.fr       */
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
		space -= (sign < 0);
	}
	else if (((f.minus && end) || (!f.minus && !end)) && !f.zero)
		space = f.width - len;
	ft_putcharn(' ', space - (sign > 0 && (f.space || f.plus)));
	if (!end && sign > 0)
	{
		if (f.space)
			ft_putchar(' ');
		if (f.plus)
			ft_putchar('+');
	}
}

static int	num_writer(long long n, t_flags f)
{
	int	len;
	int	has_prefix;

	has_prefix = ((f.plus || f.space) && n >= 0);
	len = ft_getnumlen_llong(n);
	if (f.precision == 0 && n == 0)
		len = 0;
	else if (f.zero && f.width > 0 && f.precision != -1)
		len = ft_max(f.precision - (f.plus && n >= 0) + (n < 0), len);
	else if (f.zero && f.width > 0 && f.precision == -1)
		len = ft_max(f.width - has_prefix, len);
	else
		len = ft_max(f.precision + (n < 0), len);
	print_cap(f, ft_getsign_llong(n), len, 0);
	ft_putnbrn_llong(n, len);
	print_cap(f, ft_getsign_llong(n), len, 1);
	if (f.width)
		return (ft_max(len + has_prefix, ft_max(f.width, f.precision)));
	return (len + has_prefix);
}

int	num_handler(va_list args, t_flags flags)
{
	if (ft_strequ(flags.length, "h"))
		return (num_writer((short) va_arg(args, int), flags));
	if (ft_strequ(flags.length, "hh"))
		return (num_writer((char) va_arg(args, int), flags));
	if (ft_strequ(flags.length, "l"))
		return (num_writer(va_arg(args, long), flags));
	if (ft_strequ(flags.length, "ll"))
		return (num_writer(va_arg(args, long long), flags));
	if (ft_strequ(flags.length, "j"))
		return (num_writer(va_arg(args, intmax_t), flags));
	if (ft_strequ(flags.length, "z"))
		return (num_writer(va_arg(args, size_t), flags));
	return (num_writer(va_arg(args, int), flags));
}
