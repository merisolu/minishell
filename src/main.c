/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/03 14:23:59 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

static int	get_state_struct(char *const **env, t_state *res)
{
	ft_bzero(res, sizeof(t_state));
	res->cursor = ft_strlen(PROMPT);
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

static int	setup(char *const **env, t_state *state)
{
	set_signal_handling();
	if (!get_state_struct(env, state))
		return (print_error(ERR_MALLOC_FAIL, 0));
	if (!configure_input(state))
		return (print_error(ERR_TERMIOS_FAIL, 0));
	return (1);
}

int	main(const int argc, const char **argv, char *const *env)
{
	t_state		state;

	(void)argc;
	(void)argv;
	if (!setup(&env, &state))
		return (1);
	print_state(&state, 0);
	while (!state.exiting)
	{
		check_signal(&state);
		if (get_input(&state) == 1)
		{
			set_prev_config(&state);
			if (!ft_strisempty(state.input))
				tokenize_and_execute(&(state.input), &state);
			if (g_last_signal == 0 && !state.exiting)
				print_state(&state, 0);
			set_raw_config(&state);
		}
	}
	if (!set_prev_config(&state))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	return (0);
}
