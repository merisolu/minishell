/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:56:40 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/11 10:38:18 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_env_args(t_shell_env *env_args, int return_value)
{
	if (env_args->args)
	{
		ft_free_null_array_elements((void **)(env_args->args + 1));
		free(env_args->args);
	}
	ft_free_null_array((void **)(env_args->env));
	return (return_value);
}

static int	handle_invalid_flag(char flag)
{
	if (ft_strchr("i", flag))
		return (0);
	ft_putstr_fd("env: illegal option -- ", STDERR_FILENO);
	ft_putchar_fd(flag, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_putendl("usage: env [-i] [name=value ...] [utility [argument ...]]");
	return (1);
}

static int	parse_args(char *const *args, char *const *env, t_shell_env *cmd)
{
	int	i;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		if (handle_invalid_flag(args[i][1]))
			return (-1);
		cmd->exclusive += (args[i][1] == 'i' || args[i][1] == '\0');
		i++;
	}
	if (cmd->exclusive)
	{
		cmd->env = (char **)ft_memalloc(sizeof(char *));
		if (!cmd->env)
			return (-1);
	}
	else if (!ft_dup_null_array((void **)env, (void ***)&(cmd->env), var_cpy))
		return (-1);
	while (args[i] && ft_strchr(args[i], '='))
	{
		if (!env_set(args[i], NULL, (char *const **)&(cmd->env)))
			free_env_args(cmd, -1);
		i++;
	}
	return (i);
}

int	cmd_env(char *const *args, char *const **env)
{
	t_shell_env	cmd;
	int			i;
	char		path[PATH_MAX];
	int			return_value;

	ft_bzero(&cmd, sizeof(t_shell_env));
	i = parse_args(args, *env, &cmd);
	if (i < 0)
		return (1);
	if (!args[i])
	{
		env_print_all(cmd.env);
		return (free_env_args(&cmd, 0));
	}
	if (!ft_dup_null_array((void **)(args + i), (void ***)&(cmd.args), var_cpy))
		return (print_error(ERR_MALLOC_FAIL, free_env_args(&cmd, 1)));
	if (!bin_env_find(args[i], *env, path))
		return (1);
	return_value = bin_execute(path, cmd.args, (char *const **)&(cmd.env));
	return (free_env_args(&cmd, return_value));
}
