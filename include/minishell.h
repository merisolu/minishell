/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:15:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/11 09:32:08 by jumanner         ###   ########.fr       */
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

# define RETURN_COMMAND_NOT_FOUND 127

/* Errors */
# define ERR_LINE_READ "Line read error."
# define ERR_FORK_FAIL "Process creation failed."
# define ERR_EXECVE_FAIL "Process execution failed."
# define ERR_COM_NOT_FOUND "Command not found."
# define ERR_TOO_FEW_ARGS "Too few arguments."
# define ERR_TOO_MANY_ARGS "Too many arguments."
# define ERR_NO_SUCH_FILE_OR_DIR "No such file or directory."
# define ERR_CANNOT_GET_CWD "Unable to get current working directory."
# define ERR_PATH_TOO_LONG "File name too long."
# define ERR_MALLOC_FAIL "Memory allocation failed."

/* Types */

typedef struct s_state
{
	char *const	*env;
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

typedef int	t_built_in(char *const *args, char *const **env);

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

/* environment.c */
char		*env_get(const char *name, char *const *env);
int			env_set(const char *name, const char *value, char *const **env);
int			env_unset(const char *name, char *const **env);
void		env_print_all(char *const *env);

/* bin.c */
void		bin_find(const char *name, char **paths, char result[PATH_MAX]);
int			bin_env_find(const char *name, char *const *env, char result[PATH_MAX]);
int			bin_execute(const char *path, char **args, char *const **env);
int			bin_run(const char *name, char *const *args, char *const **env);

/* built_ins.c */
t_built_in	*get_built_in(const char *name);
int			run_built_in(t_built_in com, char *const *args, char *const **env);

/* executor.c */
int			execute(char *name, char *const *args, t_state *state);

/* Built-in commands */

/* echo.c */
int			echo(char *const *args, char *const **env);

/* cd.c */
int			cd(char *const *args, char *const **env);

/* env.c */
int			env(char *const *args, char *const **env);

/* set_env.c */
int			set_env(char *const *args, char *const **env);

/* unset_env.c */
int			unset_env(char *const *args, char *const **env);

/* exit.c */
int			shell_exit(char *const *args, char *const **env);

/* Utilities */

/* utils.c */
int			print_error(char *message, int return_value);
void		*var_cpy(void *var);

/* debug.c */
void		print_tokens(t_token *list);

#endif
