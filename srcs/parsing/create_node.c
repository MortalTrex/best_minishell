/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:03:55 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/08 15:25:09 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *create_cmd_node(void)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->type = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	node->file = NULL;
	node->cmd = malloc(sizeof(t_cmd));
	if (!node->cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->cmd->argv = malloc(sizeof(char *) * 2); // Initial space for argv (NULL-terminated array)
	node->cmd->argv[0] = NULL;					  // For a valid NULL-terminated array
	node->cmd->next = NULL;
	node->cmd->redir = NULL;
	return node;
}

t_ast_node *create_pipe_node(void)
{
	t_ast_node *pipe_node = malloc(sizeof(t_ast_node));
	if (!pipe_node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	pipe_node->type = NODE_PIPE;
	pipe_node->left = NULL;
	pipe_node->right = NULL;
	pipe_node->file = NULL;
	pipe_node->cmd = NULL;
	return pipe_node;
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
