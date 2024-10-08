/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:44 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/08 13:54:32 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <minishell.h>

typedef enum e_redir_type
{
	IN,
	OUT,
	D_IN,
	D_OUT
}					t_redir_type;

typedef enum e_ast_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC
}					t_ast_node_type;

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	// pid_t			pid;
	struct s_cmd	*next;
	t_redir			*redir;
}					t_cmd;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	char				*file;
	t_cmd				*cmd;
}					t_ast_node;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_cmd			*cmds;
	t_env			*env;
	t_token			*tok;
	char			*user_line;
	int				*fd;
	t_ast_node		*ast;
	// t_struct	termios	term;
}					t_data;

#endif
