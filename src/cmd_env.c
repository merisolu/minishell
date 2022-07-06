/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:56:40 by jumanner          #+#    #+#             */
/*   Updated: 2022/07/06 10:38:33 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_env_args(t_cmd_env *env_args, int return_value)
{
	ft_free_null_array((void **)(env_args->args));
	ft_free_null_array((void **)(env_args->env));
	return (return_value);
}

static int	print_env_error(char *str1, char *str2, char *str3, int value)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putstr_fd(str3, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (value);
}

static int	args_to_env(char *const *args, char *const *env, int *index, \
t_cmd_env *cmd)
{
	char	*pair;
	char	*temp;

	if (cmd->exclusive)
	{
		cmd->env = (char **)ft_memalloc(sizeof(char *));
		if (!cmd->env)
			return (-1);
	}
	else if (!ft_dup_null_array((void **)env, (void ***)&(cmd->env), var_copy))
		return (-1);
	while (args[*index] && ft_strchr(args[*index], '='))
	{
		pair = args[*index];
		temp = ft_strchr(pair, '=') + 1;
		pair[ft_dstchr(pair, '=', ft_strlen(pair))] = '\0';
		if (!env_set(pair, temp, (char *const **)&(cmd->env)))
			return (free_env_args(cmd, -1));
		(*index)++;
	}
	return (0);
}

static int	parse_args(char *const *args, char *const *env, t_cmd_env *cmd)
{
	int	i;
	int	o;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		o = 1;
		while (args[i][o])
		{
			if (args[i][o] == 'i')
				cmd->exclusive = 1;
			else
				return (print_env_error(
						"illegal option -- ", args[i] + 1,
						"\nusage: env [-i] [name=value ...] \
[utility [argument ...]]", -1)
				);
			o++;
		}
		i++;
	}
	if (args_to_env(args, env, &i, cmd) == -1)
		return (-1);
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
		return (print_env_error(args[i], ": ", ERR_NO_SUCH_FILE_OR_DIR,
				free_env_args(&cmd, 1)));
	return_value = bin_execute(path, cmd.args, cmd.env);
	free(path);
	return (free_env_args(&cmd, return_value));
}
