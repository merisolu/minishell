/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:28:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/12 14:16:44 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialize_digits(t_digits *digits)
{
	int	i;

	i = 0;
	digits->ints = 1;
	digits->decis = 1;
	while (i < FLT_SIZE)
	{
		digits->digits[i] = 0;
		i++;
	}
}
