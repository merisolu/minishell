/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/28 16:18:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	int		line_read_result;

	input = NULL;
	while (1)
	{
		ft_putstr(PROMPT);
		line_read_result = 0;
		line_read_result = ft_get_next_line(STDIN_FILENO, &input);
		if (line_read_result == 1)
		{
			parse(tokenize(input));
			free(input);
		}
		else if (line_read_result == -1)
		{
			ft_putendl_fd(ERR_LINE_READ, STDERR_FILENO);
			exit(1);
		}
	}
	return (0);
}
