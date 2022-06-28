/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:13:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/28 10:26:25 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Outputs the ANSI escape sequence for requesting the cursor's position.
 *
 * The output is then parsed and saved by parse_cursor().
 */
void	save_cursor(void)
{
	ft_putstr_fd("\033[6n", STDIN_FILENO);
}

/*
 * Parses the ANSI escape sequence which reports the current cursor's position.
 * The format is: ESC[{ROW};{COLUMN}R.
 *
 * After the output has been parsed, the row and column are stored in *state.
 */
int	parse_cursor(char buf[BUF_SIZE], t_state *state)
{
	size_t	x;
	size_t	y;
	size_t	i;

	if (ft_dstchr(buf, 'R', BUF_SIZE - 1) == BUF_SIZE)
		return (0);
	x = 0;
	y = 0;
	i = 2;
	while (buf[i] != ';')
	{
		y *= 10;
		y += buf[i] - '0';
		i++;
	}
	i++;
	while (buf[i] != 'R')
	{
		x *= 10;
		x += buf[i] - '0';
		i++;
	}
	state->input_start_x = x;
	state->input_start_y = y;
	return (i + 1);
}

/*
 * Restores the cursor to the position saved in *state by outputting the ANSI
 * escape sequence for moving the cursor. The format is: ESC[{ROW};{COLUMN}H
 */
void	load_cursor(t_state *state)
{
	ft_printf("\033[%zu;%zuH", state->input_start_y, state->input_start_x);
}
