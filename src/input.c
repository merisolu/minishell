/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/28 10:30:02 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!(buf[0] == 0x7F && ft_strlen(state->input) > 0
			&& state->cursor > ft_strlen(PROMPT)))
		return (0);
	temp = ft_strdelchar(state->input, state->cursor - ft_strlen(PROMPT) - 1);
	if (!temp)
		return (-1);
	free(state->input);
	state->input = temp;
	state->cursor--;
	print_state(state);
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
		if (ft_isprint(buf[i]))
		{
			temp = ft_strins(state->input,
					state->cursor - ft_strlen(PROMPT) - 1, buf[i]);
			if (!temp)
				return (-1);
			free(state->input);
			state->input = temp;
			print_state(state);
		}
		i++;
	}
	return (0);
}
