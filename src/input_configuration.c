/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_configuration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:20:24 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/29 13:35:56 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_raw_config(t_state *state)
{
	if (fcntl(STDIN_FILENO, F_SETFL, state->flags) == -1
		|| tcsetattr(STDIN_FILENO, TCSANOW, &(state->conf)) == -1)
		return (0);
	return (1);
}

int	set_prev_config(t_state *state)
{
	if (fcntl(STDIN_FILENO, F_SETFL, state->prev_flags) == -1
		|| tcsetattr(STDIN_FILENO, TCSANOW, &(state->prev_conf)) == -1)
		return (0);
	return (1);
}

/*
 * Configures the terminal input with the following settings:
 * - Enables continuous input from STDIN (O_NONBLOCK).
 * - Disables input canonicalization and echoing (ICANON and ECHO).
 * - Enables signal generation (ISIG).
 * 
 * The original termios struct is stored in state->prev_conf, and the new one
 * in state->conf. Similarly state->prev_flags is set to the earlier fcntl flags
 * and the new ones are stored in state->flags.
 * 
 * At the end of the function, set_raw_config() is called to set the proper
 * input state for the shell.
 * 
 * Returns 1 on success, 0 on error.
 */
int	configure_input(t_state *state)
{
	if (tcgetattr(STDIN_FILENO, &(state->conf)) == -1)
		return (0);
	state->prev_conf = state->conf;
	state->conf.c_lflag &= ~(ICANON | ECHO);
	state->conf.c_lflag |= ISIG;
	state->flags = fcntl(STDIN_FILENO, F_GETFL);
	if (state->flags == -1)
		return (0);
	state->prev_flags = state->flags;
	state->flags |= O_NONBLOCK;
	return (set_raw_config(state));
}
