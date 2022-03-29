/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:11:09 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/28 16:10:06 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token **token)
{
	if (!token || !(*token))
		return ;
	free((*token)->value);
	free((*token));
}

void	free_token_list(t_token **list)
{
	t_token	*cursor;
	t_token	*temp;

	cursor = *list;
	while (cursor)
	{
		temp = cursor->next;
		free_token(&cursor);
		cursor = temp;
	}
	*list = NULL;
}
