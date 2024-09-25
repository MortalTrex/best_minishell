/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:58:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/09/25 16:17:56 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	default:
		printf("UNKNOWN NODE TYPE\n");
		break;
	}
	if (root->left)
		print_ast(root->left, depth + 1);
	if (root->right)
		print_ast(root->right, depth + 1);
}

t_ast_node	*parse_input(t_token **tokens)
{
	return (parse_pipeline(tokens));
}

void parse_tokens(t_data *data)
{
	printf("Parsing tokens...\n");
	ft_expand_env_vars(&data->tok);
	data->ast = parse_pipeline(&data->tok);
	printf("AST constructed, printing...\n");
	print_ast(data->ast, 0);
}
