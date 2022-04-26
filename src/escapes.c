/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escapes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:58:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/26 11:25:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_cursor(char buf[BUF_SIZE])
{
	if (buf[2] == 0x41 || buf[2] == 0x42)
		return (3);
	else if (buf[2] == 0x43)
		ft_putstr("\033[1C");
	else if (buf[2] == 0x44)
		ft_putstr("\033[1D");
	else
		return (0);
	return (3);
}

int	check_escape_sequence(char buf[BUF_SIZE])
{
	size_t									i;
	const static t_input_handler_dispatch	dispatch_table[] = {
	{0x5B, &handle_cursor},
	{0, NULL}
	};

	if (buf[0] != 0x1B)
		return (0);
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (dispatch_table[i].control_char == buf[1])
			return (dispatch_table[i].run(buf));
		i++;
	}
	return (0);
}
