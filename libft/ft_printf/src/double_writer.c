/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_writer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:28:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/18 11:59:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Transforms the given double to a t_digits struct.
 * 
 * The ft_frexp call sets the value of nbr to the fraction part of the original
 * number, and stores the exponent in integer_part.
 * 
 * The first loop then uses the fractional portion of the double to reconstruct
 * the actual number by repeatedly multiplying it by two and capturing the
 * carry each time.
 * 
 * Example for the number 212.0:
 * It's essentially stored in the double like this:
 * 212.0 = 0.828125 * 2^8
 * But the above can also be represented like this:
 * 212.0 = 0.828125 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
 * 
 * The loop uses the multiply_by_two function to do the latter calculation into
 * the t_digits struct, in which each digit is stored separately. This way the
 * exact value of the double can be parsed.
 * 
 * After the first loop, only the second or the third loop run. Never both.
 * 
 * The second while loop is ran if there's still multiplication to be done (we
 * haven't fully "depleted" the exponent).
 * 
 * The third while loop's divisions are only needed for numbers with something
 * in the decimals place (we've multiplied "too much").
 */
void	transform_double(double nbr, t_digits *digits)
{
	int			exponent;
	double		integer_part;

	initialize_digits(digits);
	if (ft_getsign_double(nbr) == -1)
		nbr = -nbr;
	nbr = ft_frexp(nbr, &exponent);
	while (nbr > 0)
	{
		exponent--;
		nbr = ft_modf(nbr, &integer_part) * 2;
		multiply_by_two(digits, integer_part);
	}
	exponent++;
	while (exponent > 0)
	{
		exponent--;
		multiply_by_two(digits, 0);
	}
	while (exponent < 0)
	{
		exponent++;
		divide_by_two(digits);
	}
}

/*
 * Transforms the given long double to a t_digits struct.
 * 
 * The ft_frexp call sets the value of nbr to the fraction part of the original
 * number, and stores the exponent in integer_part.
 * 
 * The first loop then uses the fractional portion of the long double to
 * reconstruct the actual number by repeatedly multiplying it by two and
 * capturing the carry each time.
 * 
 * Example for the number 212.0:
 * It's essentially stored in the long double like this:
 * 212.0 = 0.828125 * 2^8
 * But the above can also be represented like this:
 * 212.0 = 0.828125 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
 * 
 * The loop uses the multiply_by_two function to do the latter calculation into
 * the t_digits struct, in which each digit is stored separately. This way the
 * exact value of the long double can be parsed.
 * 
 * After the first loop, only the second or the third loop run. Never both.
 * 
 * The second while loop is ran if there's still multiplication to be done (we
 * haven't fully "depleted" the exponent).
 * 
 * The third while loop's divisions are only needed for numbers with something
 * in the decimals place (we've multiplied "too much").
 */
void	transform_long_double(long double nbr, t_digits *digits)
{
	int			exponent;
	long double	integer_part;

	initialize_digits(digits);
	if (ft_getsign_ldouble(nbr) == -1)
		nbr = -nbr;
	nbr = ft_frexpl(nbr, &exponent);
	while (nbr > 0)
	{
		exponent--;
		nbr = ft_modfl(nbr, &integer_part) * 2;
		multiply_by_two(digits, integer_part);
	}
	exponent++;
	while (exponent > 0)
	{
		exponent--;
		multiply_by_two(digits, 0);
	}
	while (exponent < 0)
	{
		exponent++;
		divide_by_two(digits);
	}
}

void	print_digits(t_digits *digits, t_flags f, int width, int precision)
{
	int			i;

	ft_putcharn('0', width - digits->ints - precision);
	i = HFLT_SIZE + digits->ints;
	while (i > HFLT_SIZE - digits->decis)
	{
		i--;
		ft_putnbr(digits->digits[i]);
		if (i <= HFLT_SIZE - precision + 1 - (precision == 0))
		{
			if (f.precision == 0 && f.hash)
				ft_putchar('.');
			break ;
		}
		if (i == HFLT_SIZE)
			ft_putchar('.');
	}
	while (i > HFLT_SIZE - precision + 1)
	{
		ft_putnbr(0);
		i--;
	}
}
