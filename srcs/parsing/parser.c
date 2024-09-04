#include "minishell.h"

t_ast_node *parse_command(t_token **tokens);
t_ast_node *parse_pipeline(t_token **tokens);
t_ast_node *parse_sequence(t_token **tokens);

t_ast_node *parse_command(t_token **tokens)
{
	t_token *token = *tokens;
	if (token && token->type == T_WORD)
	{
		*tokens = token->next;
		return (create_ast_node(NODE_COMMAND, token->value));
	}
	return (NULL);
}

t_ast_node *parse_pipeline(t_token **tokens)
{
	t_ast_node *left = parse_command(tokens);
	t_token *token = *tokens;

	if (left && token && token->type == T_OPERATOR && strcmp(token->value, "|") == 0)
	{
		*tokens = token->next;
		t_ast_node *right = parse_pipeline(tokens);
		if (right)
		{
			t_ast_node *node = create_ast_node(NODE_PIPE, "|");
			node->left = left;
			node->right = right;
			return (node);
		}
	}
	return (left);
}

t_ast_node *parse_sequence(t_token **tokens)
{
	t_ast_node *left = parse_pipeline(tokens);
	t_token *token = *tokens;

	if (left && token && token->type == T_OPERATOR && strcmp(token->value, ";") == 0)
	{
		*tokens = token->next;
		t_ast_node *right = parse_sequence(tokens);
		if (right)
		{
			t_ast_node *node = create_ast_node(NODE_SEQUENCE, ";");
			node->left = left;
			node->right = right;
			return (node);
		}
	}
	return (left);
}

t_ast_node *parse_tokens(t_token *tokens)
{
	return (parse_sequence(&tokens));
}
