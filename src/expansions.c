/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/05 15:12:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_param(t_token **cursor, t_state *state, char ***res)
{
	t_token	*orig;

	orig = *cursor;
	if (!expect_token(cursor, TOKEN_TILDE, orig))
		return (0);
	if (*cursor == NULL || expect_token(cursor, TOKEN_WHITESPACE, orig))
	{
		if (env_get("HOME", state->env) && !state->in_double_quotes)
			return (
				add_to_result(res, env_get("HOME", state->env), state)
			);
		else
			return (add_to_result(res, "~", state));
	}
	return (0);
}

int	expand_tilde(t_token **cursor, t_state *state, char ***res)
{
	t_token	*orig;

	orig = *cursor;
	if (!expect_token(cursor, TOKEN_DOLLAR, orig))
		return (0);
	if (expect_token(cursor, TOKEN_LITERAL, orig))
		return (
			add_to_result(res, env_get(orig->next->value, state->env), state)
		);
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
