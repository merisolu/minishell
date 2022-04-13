/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/13 14:49:17 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_param(t_token **cursor, t_state *state, char ***result)
{
	t_token	*original;

	original = *cursor;
	if (!expect_token(cursor, TOKEN_TILDE, original))
		return (0);
	if (*cursor == NULL || expect_token(cursor, TOKEN_WHITESPACE, original))
	{
		if (env_get("HOME", state->env))
			add_to_result(result, env_get("HOME", state->env));
		else
			add_to_result(result, "~");
		return (1);
	}
	return (0);
}

int	expand_tilde(t_token **cursor, t_state *state, char ***result)
{
	t_token	*original;

	original = *cursor;
	if (!expect_token(cursor, TOKEN_DOLLAR, original))
		return (0);
	if (expect_token(cursor, TOKEN_LITERAL, original))
	{
		add_to_result(result, env_get(original->next->value, state->env));
		return (1);
	}
	if (expect_token(cursor, TOKEN_DOLLAR, original)
		&& expect_token(cursor, TOKEN_CURLY_OPEN, original)
		&& expect_token(cursor, TOKEN_LITERAL, original)
		&& expect_token(cursor, TOKEN_CURLY_CLOSED, original))
	{
		add_to_result(result, env_get(original->next->next->value, state->env));
		return (1);
	}
	return (0);
}
