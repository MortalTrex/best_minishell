#ifndef AST_H
# define AST_H

# include "minishell.h"
typedef enum e_ast_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT,
	NODE_SEQUENCE
}			t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type type;
	char *value;
	struct s_ast_node *left;
	struct s_ast_node *right;
}			t_ast_node;

#endif
