#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_ast_node *create_ast_node(t_ast_node_type type, char *value)
{
	t_ast_node *node;

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
}

void print_ast(t_ast_node *root, int depth)
{
	if (!root)
		return;

	for (int i = 0; i < depth; i++)
		printf("  "); // Indentation for depth

	switch (root->type)
	{
	case NODE_COMMAND:
		printf("COMMAND: %s\n", root->value);
		break;
	case NODE_PIPE:
		printf("PIPE: %s\n", root->value);
		break;
	case NODE_REDIRECT:
		printf("REDIRECT: %s\n", root->value);
		break;
	case NODE_SEQUENCE:
		printf("SEQUENCE: %s\n", root->value);
		break;
	default:
		printf("UNKNOWN NODE TYPE\n");
		break;
	}

	print_ast(root->left, depth + 1);
	print_ast(root->right, depth + 1);
}
