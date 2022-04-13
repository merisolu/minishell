/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/13 14:36:35 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_state	get_state_struct(char *const **env)
{
	t_state	result;

	ft_bzero(&result, sizeof(t_state));
	// TODO: Check dup array result.
	ft_dup_null_array((void **)*env, (void ***)&(result.env), var_cpy);
	return (result);
}

int	main(const int argc, const char **argv, char *const *env)
{
	t_state		state;
	char		*input;
	char		**args;
	int			line_read_result;

	(void)argc;
	(void)argv;
	state = get_state_struct(&env);
	while (1)
	{
		ft_putstr(PROMPT);
		line_read_result = 0;
		line_read_result = ft_get_next_line(STDIN_FILENO, &input);
		if (line_read_result == 1)
		{
			args = parse(tokenize(input), &state);
			if ((args[0]))
				execute(args[0], args, &state);
			free(input);
			ft_free_null_array((void **)args);
		}
		else if (line_read_result == -1)
			exit(print_error(ERR_LINE_READ, 1));
	}
	return (0);
}
