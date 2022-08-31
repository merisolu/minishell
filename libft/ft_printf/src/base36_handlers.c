/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base36_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:58:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/31 11:44:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_allocations(char **prefix, char **str, long long value)
{
	*prefix = ft_strnew(2);
	ft_strcpy(*prefix, "0z");
	*str = ft_itoa_llong_base(value, 36);
	if (!(*prefix) || !(*str))
	{
		free(*prefix);
		free(*str);
		return (0);
	}
	return (1);
}

static int	get_length(char *string, long long value, t_flags f)
{
	int	result;

	result = ft_max(ft_strlen_int(string), f.precision);
	if (f.precision == 0 && value == 0)
		result = 0;
	else if (f.hash && value != 0)
		result += 2;
	return (result);
}

static int	b36_writer(long long value, t_flags f, char *(*mod)(char *))
{
	char	*str;
	char	*prefix;
	int		len;

	if (!get_allocations(&prefix, &str, value))
		return (0);
	len = get_length(str, value, f);
	if (!f.minus && !f.zero)
		insert_width(f, len);
	if (f.hash && value != 0)
		ft_putstr(mod(prefix));
	if (!f.minus && f.zero)
		insert_width(f, len);
	insert_precision(f, ft_strlen_int(str));
	if (!(f.precision == 0 && value == 0))
		ft_putstr(mod(str));
	free(prefix);
	free(str);
	if (f.minus)
		insert_width(f, ft_max(f.precision, len));
	if (f.width)
		return (ft_max(len, ft_max(f.width, f.precision)));
	return (ft_max(len, f.precision));
}

int	b36_handler(va_list args, t_flags f, char *(*mod)(char *))
{
	if (ft_strequ(f.length, "h"))
		return (b36_writer((unsigned short) va_arg(args, int), f, mod));
	if (ft_strequ(f.length, "hh"))
		return (b36_writer((unsigned char) va_arg(args, int), f, mod));
	if (ft_strequ(f.length, "l"))
		return (b36_writer(va_arg(args, unsigned long), f, mod));
	if (ft_strequ(f.length, "ll"))
		return (b36_writer(va_arg(args, unsigned long long), f, mod));
	if (ft_strequ(f.length, "j"))
		return (b36_writer(va_arg(args, uintmax_t), f, mod));
	return (b36_writer(va_arg(args, unsigned int), f, mod));
}
