#ifndef AST_H
# define AST_H

# include "minishell.h"
# include "lexer.h" 

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

t_ast_node *create_ast_node(t_ast_node_type type, char *value);
void free_ast(t_ast_node *root);
void print_ast(t_ast_node *root, int depth);

t_ast_node *parse_command(t_token **tokens);
t_ast_node *parse_pipeline(t_token **tokens);
t_ast_node *parse_sequence(t_token **tokens);
t_ast_node *parse_tokens(t_token *tokens);

#endif
