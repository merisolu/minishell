/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:15:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/05/03 13:40:19 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>

# define PROMPT "$> "

# define BUF_SIZE 16

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
# define ERR_TERMIOS_FAIL "failed to set terminal attributes"

/* Signals */
# define SIG_HUP 1
# define SIG_INT 2
# define SIG_QUIT 3
# define SIG_ILL 4
# define SIG_TRAP 5
# define SIG_ABRT 6
# define SIG_EMT 7
# define SIG_FPE 8
# define SIG_KILL 9
# define SIG_BUS 10
# define SIG_SEGV 11
# define SIG_SYS 12
# define SIG_PIPE 13
# define SIG_ALRM 14
# define SIG_TERM 15
# define SIG_URG 16
# define SIG_STOP 17
# define SIG_TSTP 18
# define SIG_CONT 19
# define SIG_CHLD 20
# define SIG_TTIN 21
# define SIG_TTOU 22
# define SIG_IO 23
# define SIG_XCPU 24
# define SIG_XFSZ 25
# define SIG_VTALRM 26
# define SIG_PROF 27
# define SIG_WINCH 28
# define SIG_INFO 29
# define SIG_USR1 30
# define SIG_USR2 31

/* Types */

typedef struct s_state
{
	char *const		*env;
	char			*input;
	size_t			cursor;
	struct termios	conf;
	struct termios	prev_conf;
	int				flags;
	int				prev_flags;
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

typedef int	t_input_handler(char buf[16], t_state *state);

typedef struct s_input_handler_dispatch
{
	const char		control_char;
	t_input_handler	*run;
}	t_input_handler_dispatch;

typedef int	t_built_in(char *const *args, t_state *state);

typedef struct s_built_in_dispatch
{
	const char		*name;
	t_built_in		*run;
}	t_built_in_dispatch;

typedef int	t_parse_function(t_token **cursor, t_state *state, char ***result);

typedef struct s_built_in_env
{
	int		exclusive;
	char	**args;
	char	**env;
}	t_built_in_env;

/* Files */

/* signal.c */
void		check_signal(t_state *state);
void		set_signal_handling(void);

/* input.c */
int			get_input(t_state *state);

/* input_configuration.c */
int			configure_input(t_state *state);
int			set_raw_config(t_state *state);
int			set_prev_config(t_state *state);

/* escapes.c */
int			check_escape_sequence(char buf[BUF_SIZE], t_state *state);

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
int			run_built_in(t_built_in com, char *const *args, t_state *state);

/* executor.c */
int			execute(char *name, char *const *args, t_state *state);

/* Built-in commands */

/* cmd_echo.c */
int			cmd_echo(char *const *args, t_state *state);

/* cmd_cd.c */
int			cmd_cd(char *const *args, t_state *state);

/* cmd_env.c */
int			cmd_env(char *const *args, t_state *state);

/* cmd_setenv.c */
int			cmd_setenv(char *const *args, t_state *state);

/* cmd_unsetenv.c */
int			cmd_unsetenv(char *const *args, t_state *state);

/* cmd_exit.c */
int			cmd_exit(char *const *args, t_state *state);

/* Utilities */

/* utils.c */
void		print_state(t_state *state, int newline);
int			print_error(char *message, int return_value);
void		*var_cpy(void *var);

/* debug.c */
void		print_tokens(t_token *list);

#endif
