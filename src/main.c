/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/29 14:28:32 by jumanner         ###   ########.fr       */
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

static void	set_signal_handling(void)
{
	signal(SIG_INT, handle_sigint);
}

int	main(const int argc, const char **argv, char *const *env)
{
	t_state		state;
	int			line_read_result;

	(void)argc;
	(void)argv;
	set_signal_handling();
	if (!get_state_struct(&env, &state))
		return (print_error(ERR_MALLOC_FAIL, 1));
	if (!configure_input(&state))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	print_state(&state, 0);
	while (1)
	{
		if (g_last_signal != 0)
		{
			print_state(&state, 1);
			g_last_signal = 0;
		}
		line_read_result = get_input(&state);
		if (line_read_result == 1)
		{
			set_prev_config(&state);
			if (ft_strlen(state.input) != 0)
				tokenize_and_execute(&(state.input), &state);
			if (g_last_signal == 0)
				print_state(&state, 0);
			set_raw_config(&state);
		}
		else if (line_read_result == -1)
			return (print_error(ERR_LINE_READ, 1));
	}
	if (set_prev_config(&state))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	return (0);
}
