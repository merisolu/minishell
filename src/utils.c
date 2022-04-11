/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/11 09:31:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*var_cpy(void *var)
{
	return ((void *)ft_strdup((const char *)var));
}

/*
 * Prints the given error message to stderr, and returns the given value.
 */
int	print_error(char *message, int return_value)
{
	ft_putendl_fd(message, STDERR_FILENO);
	return (return_value);
}
