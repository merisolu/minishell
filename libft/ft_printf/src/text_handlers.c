/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:58:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/02 12:26:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	char_handler(va_list args, t_flags flags)
{
	int	inserted_width;

	inserted_width = 0;
	if (!flags.minus)
		inserted_width = insert_width(flags, 1);
	ft_putchar(va_arg(args, unsigned int));
	if (flags.minus)
		inserted_width = insert_width(flags, 1);
	return (inserted_width + 1);
}

int	string_handler(va_list args, t_flags flags)
{
	char	*string;
	int		len;
	int		inserted_width;

	inserted_width = 0;
	string = va_arg(args, char *);
	if (!string)
		string = "(null)";
	if (flags.precision != -1)
		len = ft_min(flags.precision, ft_strlen_int(string));
	else
		len = ft_strlen_int(string);
	if (!flags.minus)
		inserted_width = insert_width(flags, len);
	ft_putstrn(string, len);
	if (flags.minus)
		inserted_width = insert_width(flags, len);
	return (len + inserted_width);
}

int	pointer_handler(va_list args, t_flags f)
{
	void	*p;
	char	*string;
	int		len;

	p = va_arg(args, void *);
	string = ft_itoa_llong_base((unsigned long) p, 16);
	if (!string)
		return (0);
	len = ft_max(f.precision, ft_strlen_int(string)) + 2;
	if (p == 0 && f.precision == 0)
		len = 0;
	if (!f.minus)
		insert_width(f, len);
	ft_putstr("0x");
	if (len > 0)
	{
		ft_putcharn('0', f.precision - ft_strlen_int(string));
		ft_putstr(ft_strtolower(string));
	}
	if (f.minus)
		insert_width(f, len);
	free(string);
	if (f.width)
		return (ft_max(f.width, ft_max(f.precision, len)));
	return (ft_max(len, 2));
}

int	percentage_handler(va_list args, t_flags flags)
{
	int	inserted_width;

	(void) args;
	inserted_width = 0;
	if (!flags.minus)
		inserted_width = insert_width(flags, 1);
	ft_putchar('%');
	if (flags.minus)
		inserted_width = insert_width(flags, 1);
	return (inserted_width + 1);
}
