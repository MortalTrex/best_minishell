/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:03:55 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/08 13:38:19 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *create_cmd_node(t_cmd *cmd)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	node->type = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	node->cmd = cmd;
	node->file = NULL;
	return node;
}

t_ast_node *create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
	node->cmd = NULL;
	node->file = NULL;
	return node;
}

t_ast_node *create_redir_node(t_ast_node_type type, char *file)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->cmd = NULL;
	node->file = strdup(file); // Make a copy of the file name
	return node;
}
