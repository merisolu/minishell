/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/17 13:42:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

static int	get_state_struct(char *const **env, t_state *res)
{
	ft_bzero(res, sizeof(t_state));
	res->cursor = ft_strlen(PROMPT);
	res->history_index = -1;
	return (ft_dup_null_array((void **)*env, (void ***)&(res->env), var_cpy));
}

static int	tokenize_and_execute(char **input, t_state *state)
{
	int			result;
	char		**args;

	result = 0;
	history_store(*input, state);
	state->history_index = -1;
	state->cursor = ft_strlen(*input) + ft_strlen(PROMPT) + 1;
	ft_putstr("\033[2A");
	print_state(state, 1);
	ft_putchar('\n');
	args = parse(tokenize(*input), state);
	if (args && !ft_strisempty(args[0]))
		result = execute(args[0], args, state);
	ft_free_null_array((void **)args);
	clear_input(state);
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

static void	cleanup(t_state *state)
{
	ft_free_array_elements((void **)state->history, HISTORY_SIZE);
	ft_free_null_array((void **)(state->env));
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
			set_orig_config(&state);
			if (!ft_strisempty(state.input))
				tokenize_and_execute(&(state.input), &state);
			if (!state.exiting)
				print_state(&state, 0);
			set_input_config(&state);
			g_last_signal = 0;
		}
	}
	if (!set_orig_config(&state))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	cleanup(&state);
	return (0);
}
