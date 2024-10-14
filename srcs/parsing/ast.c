/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/14 19:39:19 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	switch (node->type)
	{
	case NODE_CMD:
		printf("Command: ");
		for (int i = 0; node->cmd && node->cmd->argv[i]; i++)
		{
			printf("%s ", node->cmd->argv[i]);
		}
		printf("\n");
		t_redir *redir = node->cmd->redir;
		while (redir)
		{
			for (int i = 0; i < level; i++)
				printf("  ");
			printf("Redirection: %s %s\n", redir->file, redir->type == IN ? "<" : redir->type == OUT ? ">"
																			  : redir->type == D_IN	 ? "<<"
																									 : ">>");
			redir = redir->next;
		}
		break;
	case NODE_PIPE:
		printf("Pipe\n");
		break;

	case NODE_REDIR_IN:
		printf("Redirection In: %s\n", node->file);
		break;

	case NODE_REDIR_OUT:
		printf("Redirection Out: %s\n", node->file);
		break;

	case NODE_REDIR_APPEND:
		printf("Redirection Append: %s\n", node->file);
		break;

	case NODE_HEREDOC:
		printf("Heredoc: %s\n", node->file);
		break;
	default:
		printf("Unknown Node Type\n");
		break;
	}
	if (node->left)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("Left Child:\n");
		print_ast(node->left, level + 1);
	}
	if (node->right)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("Right Child:\n");
		print_ast(node->right, level + 1);
	}
}

void parse_tokens(t_data *data)
{
	t_ast_node *root;

	printf("Parsing tokens...\n");
	if (!check_pipe_syntax(data->tok))
		return;
	ft_expand_env_vars(&data->tok);
	root = parse_pipe_sequence(data);
	data->ast = root;
	if (data->ast != NULL)
	{
		printf("AST constructed, printing...\n");
		print_ast(root, 0);
		free_ast(data->ast);
		data->ast = NULL;
	}
}
