#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_ast_node *create_ast_node(t_ast_node_type type, char *value)
{
	t_ast_node *node;

	printf("Creating AST node: type=%d, value=%s\n", type, value);
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value ? strdup(value) : NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void free_ast(t_ast_node *root)
{
	if (!root)
		return;
	free(root->value);
	free_ast(root->left);
	free_ast(root->right);
	free(root);
	root = NULL;
}

void print_ast(t_ast_node *root, int depth)
{
	if (!root)
	{
		printf("AST is empty.\n");
		return;
	}
	for (int i = 0; i < depth; i++)
		printf("  ");

	//tableau de pointeur sur fonction
	switch (root->type)
	{
	case NODE_COMMAND:
		printf("COMMAND: %s\n", root->value);
		break;
	case NODE_PIPE:
		printf("PIPE\n");
		break;
	case NODE_REDIRECT:
		printf("REDIRECT: %s\n", root->value);
		break;
	case NODE_SEQUENCE:
		printf("SEQUENCE\n");
		break;
	default:
		printf("UNKNOWN NODE TYPE\n");
		break;
	}
	if (root->left)
		print_ast(root->left, depth + 1);
	if (root->right)
		print_ast(root->right, depth + 1);
}

void ast_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: type=%d, value=%s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

void parse_tokens(t_data *data)
{
	printf("Parsing tokens...\n");
	ft_expand_env_vars(&data->tokens);
	data->ast = parse_sequence(&data->tokens);
	printf("AST constructed, printing...\n");
	print_ast(data->ast, 0);
}
