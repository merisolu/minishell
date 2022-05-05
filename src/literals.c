/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:05:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/05 15:08:29 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_literals(t_token **cursor, t_state *state, char ***result)
{
	t_token	*original;

	(void)state;
	original = *cursor;
	if (expect_token(cursor, TOKEN_WHITESPACE, original))
	{
		if (state->in_double_quotes)
			return (add_to_result(result, original->value, state));
		state->continue_previous_node = 0;
		return (1);
	}
	if (expect_token(cursor, TOKEN_DOUBLEQUOTE, original))
	{
		state->in_double_quotes = !state->in_double_quotes;
		return (1);
	}
	if (expect_token(cursor, TOKEN_LITERAL, original))
		return (add_to_result(result, original->value, state));
	return (0);
}
