/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:24:10 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/05 16:25:21 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env(char *const *args, char *const **env)
{
	char	*name;

	(void)env;
	name = args[1];
	if (!name)
		return (print_error(ERR_TOO_FEW_ARGS, 0));
	env_unset(name, env);
	return (0);
}
