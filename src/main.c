/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/22 15:10:34 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_prompt(void)
{
	ft_putstr(PROMPT);
}

static int	get_state_struct(char *const **env, t_state *res)
{
	ft_bzero(res, sizeof(t_state));
	return (ft_dup_null_array((void **)*env, (void ***)&(res->env), var_cpy));
}

static int	tokenize_and_execute(char **input, t_state *state)
{
	int			result;
	char		**args;

	result = 0;
	args = parse(tokenize(*input), state);
	if (args && (args[0]))
		result = execute(args[0], args, state);
	ft_free_null_array((void **)args);
	ft_strdel(input);
	return (result);
}

int	main(const int argc, const char **argv, char *const *env)
{
	t_state		state;
	char		*input;
	int			line_read_result;

	(void)argc;
	(void)argv;
	if (!configure_input())
		return (print_error(ERR_TERMIOS_FAIL, 1));
	if (!get_state_struct(&env, &state))
		return (print_error(ERR_MALLOC_FAIL, 1));
	print_prompt();
	while (1)
	{
		line_read_result = get_input(&input);
		if (line_read_result == 1)
		{
			if (ft_strlen(input) != 0)
				tokenize_and_execute(&input, &state);
			print_prompt();
		}
		else if (line_read_result == -1)
			return (print_error(ERR_LINE_READ, 1));
	}
	return (0);
}
