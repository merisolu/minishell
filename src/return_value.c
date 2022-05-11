/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:16:34 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/11 12:41:06 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Resets the state's last_return_value to 0.
 */
void	reset_return_value(t_state *state)
{
	set_return_value(0, state);
}

/*
 * Parses the given status code returned by wait() and sets
 * the last_return_value of the given state accordingly.
 */
void	set_return_value_from_status(int status, t_state *state)
{
	reset_return_value(state);
	if (WIFEXITED(status))
		set_return_value(WEXITSTATUS(status), state);
}

/*
 * Sets the state's last_return_value to return_value.
 */
void	set_return_value(int return_value, t_state *state)
{
	state->last_return_value = return_value;
}
