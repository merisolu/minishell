/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/11 14:00:42 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*var_cpy(void *var)
{
	return ((void *)ft_strdup((const char *)var));
}

void	clear_input(t_state *state)
{
	ft_strdel(&(state->input));
	state->cursor = ft_strlen(PROMPT);
}

void	print_state(t_state *state, int newline)
{
	if (newline)
		ft_putchar('\n');
	if (state->input)
		ft_printf(
			"\033[2K\033[0G%s%s\033[%zuG",
			PROMPT,
			state->input,
			state->cursor + 1);
	else
		ft_putstr(PROMPT);
}
