/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:44 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/27 17:03:51 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <minishell.h>
# include <termios.h>

extern int				g_exit_status;

typedef enum s_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HERE,
	T_FILENAME,
	T_DELIMITER,
}						t_type;

typedef struct s_token
{
	int					type;
	char				*value;
	int					quotes;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_cmd
{
	char				**cmd_args;
	bool				is_builtin;
	t_token				*redirs;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_env
{
	char				*line;
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_data
{
	char				*user_line;
	t_token				*tokens;
	t_cmd				*commands;
	int					infile_fd;
	int					outfile_fd;
	pid_t				prev_pid;
	int					pipe_fd[2];
	int					wstatus;
	char				*cmd_path;
	char				**envlist;
	char				*heredoc;
	int					stdin_old;
	int					exit_status;
	t_env				*env;
}						t_data;

#endif