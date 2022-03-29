/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:54:56 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/28 15:09:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(t_token_type type, char *value)
{
	t_token	*result;

	result = (t_token *)malloc(sizeof(t_token));
	if (!result)
		return (NULL);
	result->value = value;
	result->type = type;
	result->next = NULL;
	return (result);
}

t_token	*token_add(t_token **list, t_token_type type, char *value)
{
	t_token	*cursor;

	if (!(*list))
	{
		*list = token_new(type, value);
		return (*list);
	}
	cursor = *list;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = token_new(type, value);
	if (!(cursor->next))
		return (NULL);
	return (cursor->next);
}
