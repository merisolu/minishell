/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:11:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/18 12:25:56 by jumanner         ###   ########.fr       */
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
	if (!f.zero)
		ft_putcharn(' ', space);
	if (!end && sign > 0)
	{
		if (f.space)
			ft_putchar(' ');
		if (f.plus)
			ft_putchar('+');
	}
	if (!end && sign < 0)
		ft_putchar('-');
}

/*
 * Gets the length required to print the requested precision, including the dot.
*/
static int	get_precision_len(t_flags f)
{
	if (f.precision == -1)
		return (7);
	else if (f.precision == 0)
		return (0);
	return (f.precision + 1);
}

static int	special_writer(long double n, t_flags f)
{
	int			len;
	int			prec_len;

	prec_len = get_precision_len(f);
	len = 3;
	if ((ft_strequ(f.length, "L") && ft_isnan_long(n))
		|| ft_isnan(n))
	{
		f.plus = 0;
		f.space = 0;
	}
	print_cap(f, ft_getsign_ldouble(n), len + (ft_getsign_ldouble(n) == -1), 0);
	if ((ft_strequ(f.length, "L") && ft_isinfinite_long(n))
		|| ft_isinfinite(n))
	{
		if (ft_getsign_ldouble(n) == -1 || f.plus || f.space)
			len++;
		ft_putstr("inf");
	}
	else
		ft_putstr("nan");
	print_cap(f, ft_getsign_ldouble(n), len, 1);
	if (f.width && (long long) n != 0)
		return (ft_max(f.width, len));
	return (len);
}

static int	num_writer(long double n, t_flags f)
{
	int			len;
	int			prec;
	int			prefix;
	t_digits	digits;

	if (ft_strequ(f.length, "L"))
		transform_long_double(n, &digits);
	else
		transform_double(n, &digits);
	prec = get_precision_len(f);
	prefix = ((f.plus || f.space) && n > 0);
	round_decimals(&digits, prec);
	len = digits.ints + prec;
	print_cap(f, ft_getsign_ldouble(n), len, 0);
	print_digits(&digits, f, (f.width * f.zero) - prefix, prec);
	print_cap(f, ft_getsign_ldouble(n), len, 1);
	if (f.width && (long long) n != 0)
		return (ft_max(f.width, len));
	return (len + (ft_getsign_ldouble(n) == -1) + prefix + (!prec && f.hash));
}

int	float_handler(va_list args, t_flags flags)
{
	double		temp_double;
	long double	temp_ldouble;

	if (ft_strequ(flags.length, "L"))
	{
		temp_ldouble = va_arg(args, long double);
		if (ft_isinfinite_long(temp_ldouble) || ft_isnan_long(temp_ldouble))
			return (special_writer(temp_ldouble, flags));
		return (num_writer(temp_ldouble, flags));
	}
	temp_double = va_arg(args, double);
	if (ft_isinfinite(temp_double) || ft_isnan(temp_double))
		return (special_writer(temp_double, flags));
	return (num_writer(temp_double, flags));
}
