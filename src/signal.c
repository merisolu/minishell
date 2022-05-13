/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:20:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/13 16:08:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_signal;

static void	set_signal_int(int signal)
{
	g_last_signal = signal;
}

void	set_signal_handling(void)
{
	signal(SIG_INT, set_signal_int);
}

void	check_signal(t_state *state)
{
	if (g_last_signal == SIG_INT)
	{
		clear_input(state);
		print_state(state, 1);
	}
	g_last_signal = 0;
}
