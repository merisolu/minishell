/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:11:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/14 14:16:09 by jumanner         ###   ########.fr       */
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

int	add_to_result(char ***result, char *value)
{
	if (ft_add_to_null_array((void ***)result, ft_strdup(value)))
		return (1);
	return (print_error(ERR_MALLOC_FAIL, -1));
}

static int	check_literals(t_token **cursor, t_state *state, char ***result)
{
	t_token	*original;

	(void)state;
	original = *cursor;
	if (expect_token(cursor, TOKEN_WHITESPACE, original))
		return (1);
	if (expect_token(cursor, TOKEN_LITERAL, original))
		return (add_to_result(result, original->value));
	return (0);
}

int	run_functions(t_token **cursor, t_state *state, char ***result)
{
	int						func_return;
	static t_parse_function	*functions[] = {
		&expand_tilde,
		&expand_param,
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

	cursor = list;
	result = (char **)ft_memalloc(sizeof(char *));
	if (!result)
		return (NULL);
	while (cursor)
	{
		func_result = run_functions(&cursor, state, &result);
		if (func_result == 0 && cursor)
			add_to_result(&result, cursor->value);
		else if (func_result == -1)
			break ;
		if (cursor)
			cursor = cursor->next;
	}
	token_list_free(&list);
	return (result);
}
