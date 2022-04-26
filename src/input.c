/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/26 14:59:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_char(char buf[BUF_SIZE], int *index, t_state *state)
{
	if (buf[0] == 0xA)
	{
		state->cursor = ft_strlen(PROMPT);
		ft_putchar('\n');
		return (1);
	}
	*index += check_escape_sequence(buf, state);
	if (ft_isprint(buf[*index]))
	{
		state->cursor++;
		ft_putchar(buf[*index]);
	}
	return (0);
}

int	configure_input(void)
{
	struct termios	conf;

	if (tcgetattr(STDIN_FILENO, &conf) == -1)
		return (0);
	conf.c_lflag = ISIG;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &conf) == -1)
		return (0);
	return (1);
}

int	get_input(t_state *state)
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
		temp = ft_strnjoin(state->input, buf + i, 1);
		if (!temp)
			return (-1);
		free(state->input);
		state->input = temp;
		i++;
	}
	return (0);
}
