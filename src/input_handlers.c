/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:29:22 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/11 12:35:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_newline(char buf[BUF_SIZE], t_state *state)
{
	if (buf[0] != 0xA)
		return (0);
	state->cursor = ft_strlen(PROMPT);
	ft_putchar('\n');
	return (1);
}

int	handle_delete_word(char buf[BUF_SIZE], t_state *state)
{
	char	*temp;
	size_t	del_count;

	if (buf[0] != 0x17)
		return (0);
	if (!(ft_strlen(state->input) > 0 && state->cursor > ft_strlen(PROMPT)))
		return (0);
	temp = ft_strdelword(
			state->input, state->cursor - ft_strlen(PROMPT) - 1, &del_count
			);
	if (!temp)
		return (-1);
	free(state->input);
	state->input = temp;
	state->cursor -= del_count;
	print_state(state, 0);
	return (0);
}

int	handle_delete_char(char buf[BUF_SIZE], t_state *state)
{
	char	*temp;

	if (buf[0] != 0x7F)
		return (0);
	if (!(ft_strlen(state->input) > 0 && state->cursor > ft_strlen(PROMPT)))
		return (0);
	temp = NULL;
	temp = ft_strdelchar(state->input, state->cursor - ft_strlen(PROMPT) - 1);
	if (!temp)
		return (-1);
	free(state->input);
	state->input = temp;
	state->cursor--;
	print_state(state, 0);
	return (0);
}

int	handle_char(char buf[BUF_SIZE], int *index, t_state *state)
{
	int	return_value;

	return_value = handle_newline(buf, state);
	if (return_value != 0)
		return (return_value);
	return_value = handle_delete_char(buf, state);
	if (return_value != 0)
		return (return_value);
	return_value = handle_delete_word(buf, state);
	if (return_value != 0)
		return (return_value);
	*index += check_escape_sequence(buf, state);
	if (ft_isprint(buf[*index]))
		state->cursor++;
	return (0);
}
