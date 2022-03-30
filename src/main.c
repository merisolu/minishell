/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 14:52:43 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_state	get_state_struct(const char **env)
{
	t_state	result;

	ft_bzero(&result, sizeof(t_state));
	result.env = env;
	result.paths = ft_strsplit(env_get("PATH", env), ':');
	return (result);
}

int	main(const int argc, const char **argv, const char **env)
{
	t_state	state;
	char	*input;
	int		line_read_result;
	char	path[PATH_MAX];

	(void)argc;
	(void)argv;
	state = get_state_struct(env);
	while (1)
	{
		ft_putstr(PROMPT);
		line_read_result = 0;
		line_read_result = ft_get_next_line(STDIN_FILENO, &input);
		if (line_read_result == 1)
		{
			bin_find(input, &state, path);
			ft_printf("Path: %s\n", path);
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
