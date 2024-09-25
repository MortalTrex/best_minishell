/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:23:13 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/09/25 17:54:43 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef enum e_redir_type
{
	IN,        // Input redirection ('<')
	OUT,       // Output redirection ('>')
	D_IN,      // Heredoc redirection ('<<')
	D_OUT      // Append redirection ('>>')
} t_redir_type;


typedef enum e_ast_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC
}		t_ast_node_type;

typedef struct s_ast_node t_ast_node;

typedef struct s_redir
{
	char			*file;      // Filename or heredoc delimiter
	t_redir_type	type;       // Redirection type (IN, OUT, D_IN, D_OUT)
	struct s_redir	*next;      // Pointer to the next redirection
}	t_redir;

typedef struct s_cmd
{
	char			**argv;  // Array of arguments (including the command)
	struct s_cmd	*next;   // For chaining commands (if needed)
	t_redir			*redir;  // Redirection information for the command
}	t_cmd;


struct s_ast_node
{
	t_ast_node_type	type;
	t_ast_node		*left; // For binary tree (left and right children)
	t_ast_node		*right;
	char			*file; // For redirection nodes (stores file name or delimiter)
	t_cmd			*cmd; // For command nodes (stores command and arguments)
};

#endif
