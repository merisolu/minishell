/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/07/27 15:34:01 by jumanner         ###   ########.fr       */
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
	if (*cursor && !ft_strisempty((*cursor)->value)
		&& !ft_strchr(":/", (*cursor)->value[0]))
	{
		if ((*cursor)->value[0] == '=' && ft_strlen((*cursor)->value) > 1)
			return (add_to_result(res, "~", state));
		return (add_to_result(res, "~", state));
	}
	if (env_get("HOME", state->env) && !state->in_double_quotes)
		return (
			add_to_result(res, env_get("HOME", state->env), state)
		);
	return (add_to_result(res, "~", state));
}

int	expand_variable(t_token **cursor, t_state *state, char ***res)
{
	t_token	*original;
	char	*temp;
	int		return_code;

	original = *cursor;
	if (expect_token(cursor, TOKEN_DOLLAR, original) \
		&& expect_token(cursor, TOKEN_LITERAL, original))
	{
		temp = original->next->value;
		if (ft_strequ(temp, "?"))
		{
			temp = ft_itoa(state->last_return_value);
			return_code = add_to_result(res, temp, state);
			free(temp);
			return (return_code);
		}
		return (add_to_result(res, env_get_or(temp, "", state->env), state));
	}
	if (expect_token(cursor, TOKEN_DOLLAR, original)
		&& expect_token(cursor, TOKEN_CURLY_OPEN, original)
		&& expect_token(cursor, TOKEN_LITERAL, original)
		&& expect_token(cursor, TOKEN_CURLY_CLOSED, original))
		return (add_to_result(res, env_get_or(original->next->next->value, "",
					state->env), state));
	return (0);
}
