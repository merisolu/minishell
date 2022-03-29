/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:08:39 by jumanner          #+#    #+#             */
/*   Updated: 2022/01/26 14:46:55 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	insert_width(t_flags flags, int length)
{
	if (!flags.width)
		return (0);
	if (flags.zero && flags.precision == -1)
		ft_putcharn('0', flags.width - length);
	else
		ft_putcharn(' ', flags.width - length);
	return (ft_max(0, flags.width - length));
}

/*
 * Used for inserting additional precision for non base-10 values.
*/
int	insert_precision(t_flags flags, int length)
{
	if (flags.precision == -1)
		return (0);
	ft_putcharn('0', flags.precision - length);
	return (ft_max(0, flags.precision - length));
}
