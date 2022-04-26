/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:42:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/26 11:12:32 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (buf[0] == 0xA)
		{
			ft_putchar('\n');
			return (1);
		}
		if (ft_isprint(buf[i]))
			ft_putchar(buf[i]);
		temp = ft_strnjoin(*input, buf + i, 1);
		if (!temp)
			return (-1);
		free(*input);
		*input = temp;
		i++;
	}
	return (0);
}
