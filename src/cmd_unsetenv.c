/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:24:10 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/17 11:16:19 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_unsetenv(char *const *args, t_state *state)
{
	char	*name;

	name = args[1];
	if (!name)
		return (print_named_error("unsetenv", ERR_TOO_FEW_ARGS, 0));
	env_unset(name, &(state->env));
	return (0);
}
