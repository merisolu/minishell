/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/06 13:24:31 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_token_type(char value)
{
	if (ft_is_whitespace(value))
		return (TOKEN_WHITESPACE);
	if (value == '$')
		return (TOKEN_DOLLAR);
	if (value == '~')
		return (TOKEN_TILDE);
	if (value == '"')
		return (TOKEN_DOUBLEQUOTE);
	if (value == '{')
		return (TOKEN_CURLY_OPEN);
	if (value == '}')
		return (TOKEN_CURLY_CLOSED);
	return (TOKEN_LITERAL);
}

t_token	*tokenize(char *line)
{
	t_token	*result;
	int		type;
	int		changed;
	int		i;

	result = NULL;
	i = 0;
	while (line[i] && (int)get_token_type(line[i]) == TOKEN_WHITESPACE)
		i++;
	changed = i;
	type = get_token_type(line[i]);
	while (line[i])
	{
		if ((int)get_token_type(line[i]) != type
			|| (type != TOKEN_LITERAL && type != TOKEN_WHITESPACE))
		{
			token_add(&result, type, ft_strsub(line, changed, i - changed));
			type = get_token_type(line[i]);
			changed = i;
		}
		i++;
	}
	token_add(&result, type, ft_strsub(line, changed, i - changed));
	return (result);
}
