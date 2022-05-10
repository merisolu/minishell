/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/10 11:20:37 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_tilde(t_token **cursor, t_state *state, char ***res)
{
	char	*previous;
	t_token	*orig;

	orig = *cursor;
	if (!expect_token(cursor, TOKEN_TILDE, orig))
		return (0);
	previous = (*res)[ft_null_array_len((void **)(*res)) - 1];
	if (state->continue_previous_node
		&& !ft_strchr(":=", previous[ft_strlen(previous) - 1]))
	{
		orig = *cursor;
		return (add_to_result(res, "~", state));
	}
	if (*cursor
		&& ((*cursor)->value[0] != '/' && !ft_strisempty((*cursor)->value)))
		return (add_to_result(res, "~", state));
	if (env_get("HOME", state->env) && !state->in_double_quotes)
		return (
			add_to_result(res, env_get("HOME", state->env), state)
		);
	else
		return (add_to_result(res, "~", state));
	return (0);
}

int	expand_variable(t_token **cursor, t_state *state, char ***res)
{
	t_token	*orig;

	orig = *cursor;
	if (!expect_token(cursor, TOKEN_DOLLAR, orig))
		return (0);
	if (expect_token(cursor, TOKEN_LITERAL, orig))
	{
		if (ft_strequ(orig->next->value, "?"))
			return (add_to_result(res, ft_itoa(state->last_return_value), state));
		else
		{
			return (
				add_to_result(res, env_get(orig->next->value, state->env), state)
			);
		}
	}
	if (expect_token(cursor, TOKEN_DOLLAR, orig)
		&& expect_token(cursor, TOKEN_CURLY_OPEN, orig)
		&& expect_token(cursor, TOKEN_LITERAL, orig)
		&& expect_token(cursor, TOKEN_CURLY_CLOSED, orig))
		return (
			add_to_result(
				res, env_get(orig->next->next->value, state->env), state
			)
		);
	return (0);
}
