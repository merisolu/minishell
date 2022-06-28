/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/28 13:32:36 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

static int	get_state_struct(char *const **env, t_state *result)
{
	ft_bzero(result, sizeof(t_state));
	result->cursor = ft_strlen(PROMPT);
	result->history_index = -1;
	return (
		ft_dup_null_array((void **)*env, (void ***)&(result->env), var_copy)
	);
}

static int	tokenize_and_execute(t_state *state)
{
	int			result;
	char		**args;

	if (!set_orig_config(state))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	result = 0;
	if (ft_strisempty(state->input))
	{
		ft_putchar('\n');
		if (!set_input_config(state))
			print_error(ERR_TERMIOS_FAIL, 1);
		return (result);
	}
	history_store(state->input, state);
	state->cursor = ft_strlen(state->input) + ft_strlen(PROMPT);
	print_state(state, 1);
	ft_putchar('\n');
	args = parse(tokenize(state->input), state);
	if (args && !ft_strisempty(args[0]))
		result = execute(args[0], args, state);
	ft_free_null_array((void **)args);
	clear_input(state);
	if (!set_input_config(state))
		print_error(ERR_TERMIOS_FAIL, 1);
	return (result);
}

static int	setup(char *const **env, t_state *state)
{
	set_signal_handling();
	if (!get_state_struct(env, state))
		return (print_error(ERR_MALLOC_FAIL, 0));
	if (!configure_input(state))
		return (print_error(ERR_TERMIOS_FAIL, 0));
	state->pollfd = (struct pollfd){STDIN_FILENO, POLLIN, POLLIN};
	save_cursor();
	print_state(state, 0);
	return (1);
}

static int	cleanup(t_state *state)
{
	if (!set_orig_config(state))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	ft_free_array_elements((void **)state->history, HISTORY_SIZE);
	ft_free_null_array((void **)(state->env));
	return (state->exit_return_value);
}

int	main(const int argc, const char **argv, char *const *env)
{
	t_state		state;

	(void)argc;
	(void)argv;
	if (!setup(&env, &state))
		return (1);
	while (!state.exiting)
	{
		check_signal(&state);
		if (get_input(&state) == 1)
		{
			tokenize_and_execute(&state);
			if (!state.exiting)
			{
				if (g_last_signal != 0 && state.last_return_value > 128)
					ft_putchar('\n');
				save_cursor();
				print_state(&state, 0);
			}
			g_last_signal = 0;
		}
	}
	return (cleanup(&state));
}
