/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:11:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/29 11:57:56 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expect_token(t_token **cursor, t_token_type type)
{
	int	result;

	if (!cursor || !(*cursor))
		return (0);
	result = (*cursor)->type == type;
	(*cursor) = (*cursor)->next;
	return (result);
}

void	check_dollar(t_token *cursor)
{
	t_token	*original;

	original = cursor;
	if (expect_token(&cursor, TOKEN_LITERAL))
	{
		ft_printf("VARIABLE: %s\n", original->value);
		return ;
	}
	cursor = original;
	if (expect_token(&cursor, TOKEN_CURLY_OPEN)
		&& expect_token(&cursor, TOKEN_LITERAL)
		&& expect_token(&cursor, TOKEN_CURLY_CLOSED))
	{
		ft_printf("VARIABLE: %s\n", original->next->value);
		return ;
	}
}

void	parse(t_token *list)
{
	while (list)
	{
		if (list->type == TOKEN_DOLLAR)
			check_dollar(list->next);
		list = list->next;
	}
}
