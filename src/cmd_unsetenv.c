/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:24:10 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/03 13:37:06 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_unsetenv(char *const *args, t_state *state)
{
	char	*name;

	(void)state;
	name = args[1];
	if (!name)
		return (print_error(ERR_TOO_FEW_ARGS, 0));
	env_unset(name, &(state->env));
	return (0);
}
