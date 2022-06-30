/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:11:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/06/30 11:58:27 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks if the cursor is currently on a token with the type of 'type'.
 *
 * If it is, the cursor is advanced to (*cursor)->next, and 1 is returned.
 *
 * If not, *cursor is set to on_fail, and 0 is returned. This is also done
 * if cursor or *cursor is NULL.
 *
 * The goal was to have a "chainable function" that could be called repeatedly
 * to check if a set of tokens in a list matches a predetermined set, while also
 * allowing for easy resets to the start of the chain (for immediate checking of
 * another sequence of tokens) without having to handle it in the calling
 * function.
 */
int	expect_token(t_token **cursor, t_token_type type, t_token *on_fail)
{
	int	result;

	if (!cursor || !(*cursor))
	{
		*cursor = on_fail;
		return (0);
	}
	result = (*cursor)->type == type;
	if (result)
		(*cursor) = (*cursor)->next;
	else
		(*cursor) = on_fail;
	return (result);
}

/*
 * Adds the given value to the result array.
 *
 * The way the value is added depends on the continue_previous_node flag.
 * 		- If it's set to 1, the last string of the result array will have value
 * 		appended to it.
 * 		- If it's set to 0, a new node will be created in the result array,
 * 		with the given value.
 */
int	add_to_result(char ***result, char *value, t_state *state)
{
	char	**destination;
	char	*temp;

	if (!value)
		return (print_error(ERR_MALLOC_FAIL, -1));
	if (state->continue_previous_node)
	{
		destination = ((*result) + ft_null_array_len((void **)(*result)) - 1);
		temp = ft_strjoin(*destination, value);
		if (!temp)
			return (print_error(ERR_MALLOC_FAIL, -1));
		free(*destination);
		*destination = temp;
		return (1);
	}
	else
	{
		state->continue_previous_node = 1;
		temp = ft_strdup(value);
		if (!temp)
			return (print_error(ERR_MALLOC_FAIL, -1));
		if (ft_add_to_null_array((void ***)result, temp))
			return (1);
	}
	return (print_error(ERR_MALLOC_FAIL, -1));
}

int	run_functions(t_token **cursor, t_state *state, char ***result)
{
	int						func_return;
	static t_parse_function	*functions[] = {
		&expand_variable,
		&expand_tilde,
		&check_literals,
		NULL
	};
	size_t					i;

	i = 0;
	while (functions[i] != NULL)
	{
		func_return = (*functions[i])(cursor, state, result);
		if (func_return != 0)
			return (func_return);
		i++;
	}
	return (0);
}

/*
 * Parses the given list of tokens, handles expansions and whitespace, puts the
 * result into a char**, then returns it. 
 *
 * Returns NULL on error.
 */
char	**parse(t_token *list, t_state *state)
{
	t_token	*cursor;
	char	**result;
	int		func_result;

	state->continue_previous_node = 0;
	state->in_double_quotes = 0;
	if (!list)
		return (NULL);
	cursor = list;
	result = (char **)ft_memalloc(sizeof(char *));
	if (!result)
		return (NULL);
	while (cursor)
	{
		func_result = run_functions(&cursor, state, &result);
		if (func_result == 0 && cursor)
		{
			func_result = add_to_result(&result, cursor->value, state);
			cursor = cursor->next;
		}
		if (func_result == -1)
			break ;
	}
	token_list_free(&list);
	return (result);
}
