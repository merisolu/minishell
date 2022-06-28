/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:56:40 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/28 13:32:57 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_env_args(t_cmd_env *env_args, int return_value)
{
	ft_free_null_array((void **)(env_args->args));
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

static int	arg_to_env(char *value, t_cmd_env *cmd)
{
	char	*temp;

	temp = ft_strchr(value, '=') + 1;
	value[ft_dstchr(value, '=', ft_strlen(value))] = '\0';
	if (!env_set(value, temp, (char *const **)&(cmd->env)))
		return (free_env_args(cmd, -1));
	return (0);
}

static int	parse_args(char *const *args, char *const *env, t_cmd_env *cmd)
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
	else if (!ft_dup_null_array((void **)env, (void ***)&(cmd->env), var_copy))
		return (-1);
	while (args[i] && ft_strchr(args[i], '='))
	{
		if (arg_to_env(args[i], cmd) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	cmd_env(char *const *args, t_state *state)
{
	t_cmd_env	cmd;
	int			i;
	char		*path;
	int			return_value;

	ft_bzero(&cmd, sizeof(t_cmd_env));
	i = parse_args(args, state->env, &cmd);
	if (i < 0)
		return (1);
	if (!args[i])
	{
		env_print_all(cmd.env);
		return (free_env_args(&cmd, 0));
	}
	if (!ft_dup_null_array((void **)(args + i), (void ***)&(cmd.args),
		var_copy))
		return (
			print_named_error("env", ERR_MALLOC_FAIL, free_env_args(&cmd, 1))
		);
	if (!bin_env_find(args[i], state->env, &path))
		return (1);
	return_value = bin_execute(path, cmd.args, cmd.env, state);
	free(path);
	return (free_env_args(&cmd, return_value));
}
