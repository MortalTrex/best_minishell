/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:44 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 13:37:07 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <minishell.h>
# include <termios.h>

extern int				g_exit_code;

/* enums */
typedef enum s_type
{
	WORD,
	PIPE,
	LESS,
	GREAT,
	GREATGREAT,
	LESSLESS,
	FILENAME,
	DELIMITER,
}						t_type;

typedef struct s_token
{
	int					type;
	char				*value;
	int					quotes_status;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_command
{
	char				**cmd_name;
	bool				is_builtin;
	t_token				*redirections;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_env
{
	char				*var_name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	char				*input;
	t_token				*tokens;
	t_command			*commands;
	int					infile_fd;
	int					outfile_fd;
	pid_t				last_pid;
	int					pipe_fd[2];
	int					wstatus;
	char				*cmd_path;
	char				**env;
	char				*heredoc;
	int					old_stdin;
	int					exit_status;
	t_env				*env_list;
}						t_shell;

#endif