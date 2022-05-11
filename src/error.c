/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:57:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/11 13:57:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Prints the given error message to stderr, and returns the given value.
 */
int	print_error(char *message, int return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (return_value);
}

/*
 * Prints the given name and error message to stderr, and returns the
 * given return_value.
 */
int	print_named_error(char *name, char *message, int return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (return_value);
}
