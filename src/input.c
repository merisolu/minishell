/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/26 11:41:48 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_char(char buf[BUF_SIZE], int *index)
{
	if (buf[0] == 0xA)
	{
		ft_putchar('\n');
		return (1);
	}
	*index += check_escape_sequence(buf);
	if (ft_isprint(buf[*index]))
		ft_putchar(buf[*index]);
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

int	get_input(char **input)
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
		if (handle_char(buf, &i))
			return (1);
		temp = ft_strnjoin(*input, buf + i, 1);
		if (!temp)
			return (-1);
		free(*input);
		*input = temp;
		i++;
	}
	return (0);
}
