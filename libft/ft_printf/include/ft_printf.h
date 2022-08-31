/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:27:15 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/31 11:43:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# if __linux__
#  include <inttypes.h>
#  include <stdint.h>
# endif

# define FLT_SIZE 32800
# define HFLT_SIZE 16400

typedef struct s_flags
{
	int		minus;
	int		plus;
	int		space;
	int		hash;
	int		zero;
	int		width;
	int		precision;
	char	*length;
	char	*start;
}				t_flags;

typedef struct s_digits
{
	int	decis;
	int	ints;
	int	digits[FLT_SIZE];
}				t_digits;

int		ft_printf(const char *format, ...);

int		text_dispatch(t_flags *flags, char character, va_list args);
int		numeric_dispatch(t_flags *flags, char character, va_list args);
int		custom_dispatch(t_flags *flags, char character, va_list args, int wc);

void	parse_flags(char **cursor, t_flags *result);
void	parse_width(char **cursor, va_list args, t_flags *result);
void	parse_precision(char **cursor, va_list args, t_flags *result);
void	parse_length(char **cursor, t_flags *result);

int		parse_color(char **cursor);

int		insert_width(t_flags flags, int length);
int		insert_precision(t_flags flags, int length);

int		char_handler(va_list args, t_flags flags);
int		string_handler(va_list args, t_flags flags);
int		pointer_handler(va_list args, t_flags flags);

int		percentage_handler(va_list args, t_flags flags);

int		written_chars_handler(va_list args, int chars);

int		hex_handler(va_list args, t_flags flags, char *(*modifier)(char *));

int		oct_handler(va_list args, t_flags flags);

int		bin_handler(va_list args, t_flags f, char *(*mod)(char *));

int		b36_handler(va_list args, t_flags f, char *(*mod)(char *));

int		num_handler(va_list args, t_flags flags);
int		unum_handler(va_list args, t_flags flags);

int		float_handler(va_list args, t_flags flags);

void	initialize_digits(t_digits *digits);

void	print_digits(t_digits *digits, t_flags f, int width, int precision);

void	transform_double(double nbr, t_digits *digits);
void	transform_long_double(long double nbr, t_digits *digits);

int		multiply_by_two(t_digits *digits, int carry);
void	divide_by_two(t_digits *digits);
void	round_decimals(t_digits *digits, int decimals);

#endif
