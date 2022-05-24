/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:47:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/24 11:53:02 by jumanner         ###   ########.fr       */
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

int	expand_variable(t_token **c, t_state *state, char ***res)
{
	t_token	*og;
	char	*tmp;
	int		return_code;

	og = *c;
	if (expect_token(c, TOKEN_DOLLAR, og) && expect_token(c, TOKEN_LITERAL, og))
	{
		tmp = og->next->value;
		if (ft_strequ(tmp, "?"))
		{
			tmp = ft_itoa(state->last_return_value);
			return_code = add_to_result(res, tmp, state);
			free(tmp);
			return (return_code);
		}
		else
			return (add_to_result(res, env_get_or(tmp, "", state->env), state));
	}
	if (expect_token(c, TOKEN_DOLLAR, og)
		&& expect_token(c, TOKEN_CURLY_OPEN, og)
		&& expect_token(c, TOKEN_LITERAL, og)
		&& expect_token(c, TOKEN_CURLY_CLOSED, og))
		return (add_to_result(res, env_get_or(og->next->next->value, "",
					state->env), state));
	return (0);
}
