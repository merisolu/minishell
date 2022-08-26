/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:21:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/26 14:40:49 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_text_color(char *color_name)
{
	if (ft_strequ(color_name, "WHITE"))
		ft_putstr(TEXT_WHITE);
	else if (ft_strequ(color_name, "BLACK"))
		ft_putstr(TEXT_BLACK);
	else if (ft_strequ(color_name, "RED"))
		ft_putstr(TEXT_RED);
	else if (ft_strequ(color_name, "YELLOW"))
		ft_putstr(TEXT_YELLOW);
	else if (ft_strequ(color_name, "GREEN"))
		ft_putstr(TEXT_GREEN);
	else if (ft_strequ(color_name, "CYAN"))
		ft_putstr(TEXT_CYAN);
	else if (ft_strequ(color_name, "BLUE"))
		ft_putstr(TEXT_BLUE);
	else if (ft_strequ(color_name, "MAGNETA"))
		ft_putstr(TEXT_MAGENTA);
	else if (ft_strequ(color_name, "RESET"))
		ft_putstr(COLOR_RESET);
	else
		return (0);
	return (1);
}

static int	put_background_color(char *color_name)
{
	if (ft_strequ(color_name, "BG_BLACK"))
		ft_putstr(BG_BLACK);
	else if (ft_strequ(color_name, "BG_RED"))
		ft_putstr(BG_RED);
	else if (ft_strequ(color_name, "BG_YELLOW"))
		ft_putstr(BG_YELLOW);
	else if (ft_strequ(color_name, "BG_GREEN"))
		ft_putstr(BG_GREEN);
	else if (ft_strequ(color_name, "BG_CYAN"))
		ft_putstr(BG_CYAN);
	else if (ft_strequ(color_name, "BG_BLUE"))
		ft_putstr(BG_BLUE);
	else if (ft_strequ(color_name, "BG_MAGNETA"))
		ft_putstr(BG_MAGENTA);
	else
		return (0);
	return (1);
}

int	parse_color(char **cursor)
{
	char	*color_name;

	if (**cursor != '{' || !ft_strchr(*cursor, '}'))
		return (0);
	color_name = ft_strsub(*cursor, 1, ft_dstchr(*cursor, '}', 11) - 1);
	if (put_text_color(color_name) || put_background_color(color_name))
	{
		free(color_name);
		*cursor = ft_strchr(*cursor, '}') + 1;
		if (**cursor == '{')
			return (parse_color(cursor));
		return (1);
	}
	free(color_name);
	return (0);
}
