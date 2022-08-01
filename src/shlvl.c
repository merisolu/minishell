/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:16:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/01 11:57:36 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_shlvl_error(int target_shlvl)
{
	ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
	ft_putnbr_fd(target_shlvl, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
}

int	set_shlvl(char *const **env)
{
	int		result;
	int		shlvl;
	char	*shlvl_string;

	shlvl = 0;
	if (env_get("SHLVL", *env))
		shlvl = ft_atoi(env_get("SHLVL", *env));
	if (shlvl + 1 < 0)
		shlvl = 0;
	else if (shlvl + 1 >= 1000)
	{
		print_shlvl_error(shlvl + 1);
		shlvl = 1;
	}
	else
		shlvl++;
	shlvl_string = ft_itoa(shlvl);
	if (!shlvl_string)
		return (print_error(ERR_MALLOC_FAIL, 0));
	result = env_set("SHLVL", shlvl_string, env);
	free(shlvl_string);
	return (result);
}
