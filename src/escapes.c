/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escapes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:58:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/09 14:07:19 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_history(char buf[BUF_SIZE], t_state *state)
{
	if (buf[2] == 0x41)
		history_recall(1, state);
	else if (buf[2] == 0x42)
		history_recall(-1, state);
	else
		return (0);
	return (3);
}

static int	handle_cursor(char buf[BUF_SIZE], t_state *state)
{
	if (buf[2] == 0x43)
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

int	handle_arrows(char buf[BUF_SIZE], t_state *state)
{
	int	return_value;

	return_value = handle_history(buf, state);
	if (return_value)
		return (return_value);
	return (handle_cursor(buf, state));
}

int	check_escape_sequence(char buf[BUF_SIZE], t_state *state)
{
	size_t									i;
	const static t_input_handler_dispatch	dispatch_table[] = {
	{0x5B, &handle_arrows},
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
