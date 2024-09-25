/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:58:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/09/25 18:09:21 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to print redirection information
void print_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->file == NULL)
		{
			printf("Error: Redirection file is NULL\n");
		}
		else
		{
			switch (redir->type)
			{
			case IN:
				printf("Redirect In: ");
				break;
			case OUT:
				printf("Redirect Out: ");
				break;
			case D_IN:
				printf("Heredoc Redirect: ");
				break;
			case D_OUT:
				printf("Append Redirect: ");
				break;
			default:
				printf("Unknown Redirection Type\n");
				break;
			}
			printf("%s\n", redir->file ? redir->file : "NULL");
		}
		redir = redir->next; // Move to the next redirection
	}
}

// Recursive function to print the AST
void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return; // Base case: if the node is NULL, return

	// Increase indentation for better readability
	for (int i = 0; i < level; i++)
	{
		printf("  ");
	}

	// Print the current node's type
	switch (node->type)
	{
	case NODE_CMD:
		printf("Command: ");
		for (char **arg = node->cmd->argv; *arg; arg++)
		{
			printf("%s ", *arg);
		}
		printf("\n");
		print_redir(node->cmd->redir); // Print associated redirections
		break;

	case NODE_PIPE:
		printf("Pipe Node\n");
		break;

	case NODE_REDIR_IN:
		printf("Redirection In Node\n");
		printf("File: %s\n", node->file);
		break;

	case NODE_REDIR_OUT:
		printf("Redirection Out Node\n");
		printf("File: %s\n", node->file);
		break;

	case NODE_REDIR_APPEND:
		printf("Append Redirection Node\n");
		printf("File: %s\n", node->file);
		break;

	case NODE_HEREDOC:
		printf("Heredoc Node\n");
		printf("Delimiter: %s\n", node->file);
		break;

	default:
		printf("Unknown Node Type\n");
		break;
	}

	// Print left and right children recursively
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

void free_ast(t_ast_node *root)
{
	if (!root)
		return;
	free_ast(root->left);
	free_ast(root->right);
	free(root);
	root = NULL;
}

t_ast_node *parse(t_token *tokens)
{
	t_ast_node *root = NULL;

	while (tokens && tokens->type != T_EOF)
	{
		root = parse_expression(&tokens);
	}
	return root;
}

void parse_tokens(t_data *data)
{
	t_ast_node *root;
	printf("Parsing tokens...\n");
	ft_expand_env_vars(&data->tok);
	data->ast = parse(data->tok);
	root = data->ast;
	printf("AST constructed, printing...\n");
	print_ast(root, 0);
}
