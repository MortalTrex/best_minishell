/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/25 15:12:18 by rbalazs          ###   ########.fr       */
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
	while (node->type)
	{
		if (node->type == NODE_CMD)
		{
			printf("Command: ");
			printf("%s ", node->cmd->argv);
			printf("\n");
			t_redir *redir = node->cmd->redir;
			while (redir)
			{
				for (int i = 0; i < level; i++)
					printf("  ");
				printf("Redirection: %s %s\n", redir->file, redir->type == IN ? "<" : redir->type == OUT ? ">"
																				: redir->type == D_APPEND	 ? "<<"
																										: ">>");
				redir = redir->next;
			}
			break;
		}
		else if (node->type == NODE_PIPE)
		{
			printf("Pipe\n");
			break;
		}
		else if (node->type ==NODE_REDIR_IN)
		{
			printf("Redirection In: %s\n", node->file);
			break;
		}
		else if (node->type ==NODE_REDIR_OUT)
		{
			printf("Redirection Out: %s\n", node->file);
			break;
		}
		else if (node->type ==NODE_REDIR_APPEND)
		{
			printf("Redirection Append: %s\n", node->file);
			break;
		}
		else if (node->type ==NODE_HEREDOC)
		{
			printf("Heredoc: %s\n", node->file);
			break;
		}
		else
		{
			printf("Unknown Node Type\n");
			break;
		}
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
	printf("Parsing tokens...\n");
	// Vérifie l'emplacement des pipes pour savoir si tout est bon
	// if (!check_pipe_syntax(data->tmp_token))
	// 	return;
	// Expand les variables d'environnement, ce qui veut dire ?
	ft_expand_env_vars(&data->tok);
	// Crée l'arbre binaire
	data->ast = create_tree(data);
	if (data->ast != NULL)
	{
		printf("AST constructed, printing...\n");
		print_ast(data->ast, 0);
		free_ast(data->ast);
		data->ast = NULL;
	}
}
