/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/17 15:58:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

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

	poll(&(state->pollfd), POLLIN, -1);
	result = get_line(state);
	if (result == 1)
		return (1);
	else if (result == -1)
		return (print_error(ERR_LINE_READ, 1));
	return (result);
}
