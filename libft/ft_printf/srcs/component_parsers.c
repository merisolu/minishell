/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:36:10 by jumanner          #+#    #+#             */
/*   Updated: 2022/02/16 11:59:49 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_flags(char **cursor, t_flags *result)
{
	while (**cursor)
	{
		if (**cursor == '-')
		{
			(*result).minus = 1;
			(*result).zero = 0;
		}
		else if (**cursor == '+')
		{
			(*result).plus = 1;
			(*result).space = 0;
		}
		else if (**cursor == ' ' && !(*result).plus)
			(*result).space = 1;
		else if (**cursor == '#')
			(*result).hash = 1;
		else if (**cursor == '0' && !(*result).minus)
			(*result).zero = 1;
		else if (**cursor != ' ' && **cursor != '0')
			break ;
		(*cursor)++;
	}
}

void	parse_width(char **cursor, va_list args, t_flags *result)
{
	int	parse_mode;

	parse_mode = -1;
	while (**cursor)
	{
		if (ft_isdigit(**cursor))
		{
			if (parse_mode != 1)
				(*result).width = 0;
			(*result).width = ((*result).width * 10) + (**cursor) - '0';
			parse_mode = 1;
		}
		else if (**cursor == '*')
			(*result).width = va_arg(args, int);
		else
			break ;
		parse_mode = ft_isdigit(**cursor);
		(*cursor)++;
	}
	if ((*result).width < 0)
	{
		(*result).minus = 1;
		(*result).zero = 0;
	}
	(*result).width = ft_abs((*result).width);
}

void	parse_precision(char **cursor, va_list args, t_flags *result)
{
	if (**cursor == '.')
	{
		(*result).precision = 0;
		(*cursor)++;
	}
	else
		return ;
	while (**cursor)
	{
		if (**cursor == '.')
		{
			(*result).precision = 0;
			(*cursor)++;
			continue ;
		}
		if (ft_isdigit(**cursor))
			(*result).precision = ((*result).precision * 10) + (**cursor) - '0';
		else if (**cursor == '*')
			(*result).precision = va_arg(args, int);
		else
			break ;
		(*cursor)++;
	}
	if ((*result).precision < 0)
		(*result).precision = -1;
}

void	parse_length(char **cursor, t_flags *result)
{
	if (**cursor == 'h' && ft_strequ((*result).length, "h"))
		(*result).length = "hh";
	else if (**cursor == 'h' && !ft_strequ((*result).length, "h"))
		(*result).length = "h";
	else if (**cursor == 'l' && ft_strequ((*result).length, "l"))
		(*result).length = "ll";
	else if (**cursor == 'l' && !ft_strequ((*result).length, "l"))
		(*result).length = "l";
	else if (**cursor == 'L')
		(*result).length = "L";
	else if (**cursor == 'j')
		(*result).length = "j";
	else if (**cursor == 'z')
		(*result).length = "z";
	else if (**cursor == 't')
		(*result).length = "t";
	else
		return ;
	(*cursor)++;
	parse_length(cursor, result);
}
