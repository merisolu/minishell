/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/11 11:52:43 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

static int	handle_newline(char buf[BUF_SIZE], t_state *state)
{
	if (buf[0] != 0xA)
		return (0);
	state->cursor = ft_strlen(PROMPT);
	ft_putchar('\n');
	return (1);
}

static int	handle_delete(char buf[BUF_SIZE], t_state *state)
{
	char	*temp;
	int		mode;
	size_t	del_count;

	if (buf[0] == 0x7F)
		mode = 1;
	else if (buf[0] == 0x17)
		mode = 2;
	else
		return (0);
	if (!(ft_strlen(state->input) > 0 && state->cursor > ft_strlen(PROMPT)))
		return (0);
	temp = NULL;
	del_count = 1;
	if (mode == 1)
		temp = ft_strdelchar(state->input, state->cursor - ft_strlen(PROMPT) - 1);
	else if (mode == 2)
		temp = ft_strdelword(state->input, state->cursor - ft_strlen(PROMPT) - 1, &del_count);
	if (!temp)
		return (-1);
	free(state->input);
	state->input = temp;
	state->cursor -= del_count;
	print_state(state, 0);
	return (0);
}

static int	handle_char(char buf[BUF_SIZE], int *index, t_state *state)
{
	int	return_value;

	return_value = handle_newline(buf, state);
	if (return_value != 0)
		return (return_value);
	return_value = handle_delete(buf, state);
	if (return_value != 0)
		return (return_value);
	*index += check_escape_sequence(buf, state);
	if (ft_isprint(buf[*index]))
		state->cursor++;
	return (0);
}

static int	get_line(t_state *state)
{
	int		read_count;
	char	*temp;
	char	buf[BUF_SIZE];
	int		i;

	ft_bzero(&buf, BUF_SIZE);
	read_count = read(STDIN_FILENO, &buf, BUF_SIZE);
	i = 0;
	while (i < read_count)
	{
		if (handle_char(buf, &i, state))
			return (1);
		if (ft_isprint(buf[i]))
		{
			temp = ft_strins(state->input,
					state->cursor - ft_strlen(PROMPT) - 1, buf[i]);
			if (!temp)
				return (-1);
			free(state->input);
			state->input = temp;
			print_state(state, 0);
		}
		i++;
	}
	return (0);
}

int	get_input(t_state *state)
{
	int	result;

	result = get_line(state);
	if (result == 1)
		return (1);
	else if (result == -1)
		return (print_error(ERR_LINE_READ, 1));
	return (result);
}
