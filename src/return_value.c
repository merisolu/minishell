/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:16:34 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/10 11:21:45 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_return_value(t_state *state)
{
	set_return_value(0, state);
}

void	set_return_value_from_status(int status, t_state *state)
{
	reset_return_value(state);
	if (WIFEXITED(status))
		set_return_value(WEXITSTATUS(status), state);
}

// TODO: Doc string.
void	set_return_value(int return_value, t_state *state)
{
	state->last_return_value = return_value;
}
