#ifndef MINISHELL_H
# define MINISHELL_H

////////////////////////// INCLUDES ///////////////////////////

# include "../libft/libft.h"
# include <curses.h>            // for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <dirent.h>            // for opendir, readdir, closedir
# include <errno.h>             // for strerror, perror
# include <fcntl.h>             // for open
# include <readline/history.h>  // for add_history
# include <readline/readline.h> // for readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <signal.h>            // for signal, sigaction, sigemptyset, sigaddset, kill
# include <stdlib.h>            // for malloc, free, exit
# include <sys/stat.h>          // for stat, lstat, fstat
# include <sys/types.h>         // for wait, waitpid, wait3, wait4
# include <sys/wait.h>          // for wait, waitpid, wait3, wait4
# include <term.h>              // for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <termios.h>           // for tcsetattr, tcgetattr
# include <unistd.h>            // for write, access, read, close, fork, getcwd, chdir, dup, dup2, pipe, isatty

////////////////////////// DEFINES ////////////////////////////

#endif
