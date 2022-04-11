minishell

Limitations:
Within your mandatory part you are allowed to use the following functions:
- malloc, free
- access
- open, close, read, write
- opendir, readdir, closedir
- getcwd, chdir
- stat, lstat, fstat
- fork, execve
- wait, waitpid, wait3, wait4
- signal, kill
- exit

Built-ins:
[x] echo
[x] cd
[x] setenv
[x] unsetenv
[x] env
[x] exit

Should all built-in function names start with "shell_"?
