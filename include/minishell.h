/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:15:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/03/31 15:22:06 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>

# define PROMPT "$> "

/* Return values */
# define RETURN_SUCCESS 1
# define RETURN_FAIL -1

# define COMMAND_NOT_FOUND 127

/* Errors */
# define ERR_LINE_READ "Line read error."
# define ERR_FORK_FAIL "Process creation failed."
# define ERR_EXECVE_FAIL "Process execution failed."
# define ERR_COM_NOT_FOUND "Command not found."

/* Types */

typedef struct s_state
{
	char *const	*env;
	char		**paths;
}	t_state;

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

typedef int	t_built_in(char *const *args, char *const *env);

typedef struct s_built_in_dispatch
{
	const char		*name;
	t_built_in		*run;
}	t_built_in_dispatch;

/* Files */

/* lexer.c */
t_token		*tokenize(char *line);

/* parser.c */
void		parse(t_token *list);

/* token.c */
t_token		*token_new(t_token_type type, char *value);
t_token		*token_add(t_token **list, t_token_type type, char *value);
void		token_free(t_token **token);

/* token_list.c */
void		token_list_free(t_token **list);

/* env.c */
char		*env_get(const char *name, char *const *env);

/* bin.c */
void		bin_find(const char *name, t_state *state, char result[PATH_MAX]);
int			bin_execute(const char *path, char *const *args, char *const *env);

/* built_ins.c */
t_built_in	*get_built_in(const char *name);
int			run_built_in(t_built_in com, char *const *args, char *const *env);

/* executor.c */
int			execute(char *name, char *const *args, t_state *state);

/* Built-in commands */

/* echo.c */
int			echo(char *const *args, char *const *env);

/* debug.c */
void		print_tokens(t_token *list);

#endif
