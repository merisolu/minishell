/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escapes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:58:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/26 15:02:29 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_cursor(char buf[BUF_SIZE], t_state *state)
{
	if (buf[2] == 0x41 || buf[2] == 0x42)
		return (3);
	else if (buf[2] == 0x43)
	{
		if (state->cursor + 1 <= ft_strlen(state->input) + ft_strlen(PROMPT))
		{
			ft_putstr("\033[1C");
			state->cursor++;
		}
	}
	else if (buf[2] == 0x44)
	{
		if (state->cursor - 1 >= ft_strlen(PROMPT))
		{
			ft_putstr("\033[1D");
			state->cursor--;
		}
	}
	else
		return (0);
	return (3);
}

int	check_escape_sequence(char buf[BUF_SIZE], t_state *state)
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
			return (dispatch_table[i].run(buf, state));
		i++;
	}
	return (0);
}
