/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_writer_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:28:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/17 16:23:50 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Multiply the array of digits by two.
 * 
 * This custom function is required because each digit is stored separately.
 * The algorithm is essentially long multiplication.
 * 
 * After the while loop has finished, the final carry gets added to the end of
 * the array.
 */
int	multiply_by_two(t_digits *digits, int carry)
{
	int	i;

	i = 0;
	while (i < digits->ints)
	{
		carry += (digits->digits[HFLT_SIZE + i] * 2);
		digits->digits[HFLT_SIZE + i] = (carry % 10);
		carry /= 10;
		i++;
	}
	if (carry)
	{
		digits->digits[HFLT_SIZE + digits->ints] = carry;
		digits->ints++;
	}
	return (0);
}

/*
 * Divide the array of digits by two.
 * 
 * This custom function is required because each digit is
 * stored separately. The algorithm is essentially long division.
 * 
 * The while loop goes through the digits backwards, starting at the decimals,
 * adding each to the end of the remainder (first multiplying remainder by 10,
 * then adding the digit to the result), assigning the reminder divided by two
 * back into the digits and leaving the remainder of the division in
 * the variable, so that it can be applied to the next digit.
 * 
 * After the while loop we check if there's at least two integers in the array,
 * and that the last integer is a zero. If so, it means that we can reduce the
 * integer count by one, because the zero at the end shouldn't be counted.
 * 
 * The last if applies any leftover carry to the decimals.
 */
void	divide_by_two(t_digits *digits)
{
	int	remainder;
	int	i;

	remainder = 0;
	i = HFLT_SIZE + digits->ints;
	while (i > HFLT_SIZE - digits->decis)
	{
		i--;
		remainder = (remainder * 10) + digits->digits[i];
		digits->digits[i] = (remainder / 2);
		remainder %= 2;
	}
	if (digits->ints > 1 && digits->digits[HFLT_SIZE + digits->ints - 1] == 0)
		digits->ints--;
	if (remainder)
	{
		remainder *= 10;
		digits->decis++;
		digits->digits[HFLT_SIZE - digits->decis] = (remainder / 2);
		remainder %= 2;
	}
}

/*
 * Go through the digits, starting from the last one that's about to be printed,
 * to as far as is necessary.
*/
void	round_decimals(t_digits *digits, int decimals)
{
	int	i;
	int	round_next;

	if (digits->decis == 0)
		return ;
	round_next = 0;
	i = HFLT_SIZE - decimals;
	while (i < HFLT_SIZE - decimals + 1 || round_next)
	{
		if (digits->digits[i] >= 5 || round_next)
		{
			digits->digits[i + 1] = (digits->digits[i + 1] + 1) % 10;
			round_next = (digits->digits[i + 1] == 0);
			if (i >= HFLT_SIZE && i >= HFLT_SIZE + digits->ints - 1)
				digits->ints++;
		}
		else
			round_next = 0;
		i++;
	}
}
