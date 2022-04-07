/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:12:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/07 13:02:35 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char *const *args, char *const **env)
{
	int		no_newline;
	size_t	len;
	size_t	i;

	(void)env;
	len = ft_null_array_len((void **)args);
	i = 1;
	no_newline = ft_strequ(args[i], "-n");
	i += no_newline;
	while (i < len)
	{
		ft_putstr(args[i]);
		if (i != len - 1)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (0);
}
