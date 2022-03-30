/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:15:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/30 11:41:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define PROMPT "$> "

/* Return values */
# define RETURN_SUCCESS 1
# define RETURN_FAIL -1

/* Errors */
# define ERR_LINE_READ "Line read error."

/* Types */

typedef enum e_token_type
{
	TOKEN_LITERAL,
	TOKEN_WHITESPACE,
	TOKEN_DOLLAR,
	TOKEN_TILDE,
	TOKEN_CURLY_OPEN,
	TOKEN_CURLY_CLOSED
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* Files */

/* lexer.c */
t_token	*tokenize(char *line);

/* parser.c */
void	parse(t_token *list);

/* token.c */
t_token	*token_new(t_token_type type, char *value);
t_token	*token_add(t_token **list, t_token_type type, char *value);
void	token_free(t_token **token);

/* token_list.c */
void	token_list_free(t_token **list);

/* debug.c */
void	print_tokens(t_token *list);

#endif
