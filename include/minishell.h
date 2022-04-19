/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:15:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/04/19 10:32:43 by jumanner         ###   ########.fr       */
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
# define ERR_LINE_READ "input read error"
# define ERR_CHILD_PROC_FAIL "cannot make child process"
# define ERR_COM_NOT_FOUND "command not found"
# define ERR_TOO_FEW_ARGS "too few arguments"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_NO_SUCH_FILE_OR_DIR "no such file or directory"
# define ERR_CANNOT_GET_CWD "error retrieving current directory"
# define ERR_INVALID_PATH "path is invalid"
# define ERR_MALLOC_FAIL "memory allocation failed"

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

typedef int	t_parse_function(t_token **cursor, t_state *state, char ***result);

typedef struct s_shell_env
{
	int		exclusive;
	char	**args;
	char	**env;
}	t_shell_env;

/* Files */

/* lexer.c */
t_token		*tokenize(char *line);

/* parser.c */
char		**parse(t_token *list, t_state *state);
int			expect_token(t_token **cursor, t_token_type type, t_token *on_fail);
int			add_to_result(char ***result, char *value);

/* expansions.c */
int			expand_param(t_token **cursor, t_state *state, char ***result);
int			expand_tilde(t_token **cursor, t_state *state, char ***result);

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
void		bin_find(const char *name, char **paths, char **result);
int			bin_env_find(const char *name, char *const *env, char **result);
int			bin_execute(const char *path, char **args, char *const **env);
int			bin_run(const char *name, char *const *args, char *const **env);

/* built_ins.c */
t_built_in	*get_built_in(const char *name);
int			run_built_in(t_built_in com, char *const *args, char *const **env);

/* executor.c */
int			execute(char *name, char *const *args, t_state *state);

/* Built-in commands */

/* cmd_echo.c */
int			cmd_echo(char *const *args, char *const **env);

/* cmd_cd.c */
int			cmd_cd(char *const *args, char *const **env);

/* cmd_env.c */
int			cmd_env(char *const *args, char *const **env);

/* cmd_setenv.c */
int			cmd_setenv(char *const *args, char *const **env);

/* cmd_unsetenv.c */
int			cmd_unsetenv(char *const *args, char *const **env);

/* cmd_exit.c */
int			cmd_exit(char *const *args, char *const **env);

/* Utilities */

/* utils.c */
int			print_error(char *message, int return_value);
void		*var_cpy(void *var);

/* debug.c */
void		print_tokens(t_token *list);

#endif
