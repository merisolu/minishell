/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/02 10:02:50 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

static int	append_input(t_state *state, char character)
{
	char	*temp;

	temp = ft_strins(state->input,
			state->cursor - ft_strlen(PROMPT) - 1, character);
	if (!temp)
		return (-1);
	free(state->input);
	state->input = temp;
	return (1);
}

static int	get_line(t_state *state)
{
	int		read_count;
	char	buf[BUF_SIZE];
	int		i;

	ft_bzero(&buf, BUF_SIZE);
	read_count = read(STDIN_FILENO, &buf, BUF_SIZE);
	if (read_count == 0)
		return (-2);
	i = check_escape_sequence(buf, state);
	while (i < read_count)
	{
		if (handle_char(buf, &i, state) == 1)
			return (1);
		if (buf[i] == '\t')
			autocomplete(state);
		else if (ft_isprint(buf[i]))
		{
			if (append_input(state, buf[i]) != 1)
				return (-1);
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
	else if (result != -2)
		print_state(state, 1);
	return (result);
}
