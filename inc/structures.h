/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:44 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/03 17:20:41 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <minishell.h>

typedef enum e_redir_type
{
	IN,
	OUT,
	D_APPEND,
	D_HEREDOC
}					t_redir_type;

typedef enum e_ast_node_type
{
	NODE_CMD,
	NODE_PIPE,
}					t_ast_node_type;

typedef struct s_redir
{
	char			*command;
	char			**argv;
	t_redir_type	type;
	int				hd_fd;
	struct s_redir	*prev;
	struct s_redir	*next;
}					t_redir;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	char				*command;
	char				**argv;
	// pid_t			pid;
	t_redir				*redir;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}					t_ast_node;

typedef struct s_env
{
	char			*line;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_env			*env;
	char			**envc;
	t_token			*tok;
	char			*user_line;
	int				fd[2];
	t_ast_node		*ast;
	int				parsing_error;
	int				exit_status;
	bool			child_signal;
	bool			heredoc_signal;
	int				free_value;
	struct termios	terminal;
}					t_data;

#endif
