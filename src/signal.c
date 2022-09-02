/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:20:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/02 10:15:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_signal;

static void	set_signal_int(int signal)
{
	g_last_signal = signal;
}

void	set_signal_handling(void)
{
	signal(SIGINT, set_signal_int);
	signal(SIGWINCH, set_signal_int);
}

void	check_signal(t_state *state)
{
	if (g_last_signal == SIGINT)
	{
		clear_input(state, 1);
		save_cursor();
		print_state(state, 0);
	}
	else if (g_last_signal == SIGWINCH)
		print_state(state, 1);
	g_last_signal = 0;
}
