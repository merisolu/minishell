/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/16 16:18:05 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned short	get_terminal_width(void)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGSIZE, &size) == -1)
		return (0);
	return (size.ws_col);
}

void	*var_cpy(void *var)
{
	return ((void *)ft_strdup((const char *)var));
}

void	clear_input(t_state *state)
{
	ft_strdel(&(state->input));
	state->cursor = ft_strlen(PROMPT);
}

/*
 * Redraws the prompt and current input.
 *
 * Redraw process:
 * 		- First the cursor position is moved back to where the start of the
 * 			prompt was printed.
 * 		- Then, the everything from the cursor to the end of the screen is
 * 			erased (this doesn't move the cursor).
 * 		- After that, the prompt and the input are printed back on to
 * 			the screen.
 * 		- Finally, the cursor is moved to the saved position.
 */
void	print_state(t_state *state, int newline)
{
	size_t	width;
	size_t	rows;

	width = get_terminal_width();
	if (width == 0)
	{
		print_error(ERR_WIDTH_GET_FAIL, 0);
		return ;
	}
	rows = ((state->prev_cursor - 1) / width);
	if (newline)
		ft_putchar('\n');
	if (state->input)
	{
		if (rows > 0)
			ft_printf("\033[%zuA", rows);
		ft_printf("\033[0G\033[0J%s%s", PROMPT, state->input);
		ft_printf("\033[%zuG", ((state->cursor - 1) % width) + 2);
		rows = (ft_strlen(state->input) + ft_strlen(PROMPT) - 1) / width;
		if (rows - ((state->cursor - 1) / width))
			ft_printf("\033[%zuA", rows - ((state->cursor - 1) / width));
	}
	else
		ft_putstr(PROMPT);
	state->prev_cursor = state->cursor;
}
