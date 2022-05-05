/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:01:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/05 14:20:29 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *list)
{
	char	*types[7];

	ft_putendl("\n-- Token list begins.");
	types[0] = "LITERAL";
	types[1] = "WHITESPACE";
	types[2] = "DOLLAR";
	types[3] = "TILDE";
	types[4] = "DOUBLE QUOTE";
	types[5] = "OPEN CURLY";
	types[6] = "CLOSED CURLY";
	while (list)
	{
		ft_printf("%s: '%s'\n", types[list->type], list->value);
		list = list->next;
	}
	ft_putendl("-- Token list ends.\n");
}
