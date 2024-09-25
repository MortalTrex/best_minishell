/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:03:55 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/09/25 19:00:39 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *create_redirect_in_node(t_ast_node *cmd_node, char *file)
{
	t_ast_node *redir_node = malloc(sizeof(t_ast_node));
	if (!redir_node)
		return NULL;

	redir_node->type = NODE_REDIR_IN;
	redir_node->left = cmd_node; // Command that receives the input
	redir_node->right = NULL;
	redir_node->file = strdup(file); // File to be used for input
	if (!redir_node->file)
	{
		perror("strdup");
		free(redir_node);
		return NULL;
	}

	// Initialize the cmd field
	redir_node->cmd = malloc(sizeof(t_cmd));
	if (!redir_node->cmd)
	{
		free(redir_node->file);
		free(redir_node);
		return NULL;
	}
	redir_node->cmd->argv = NULL;
	redir_node->cmd->next = NULL;
	redir_node->cmd->redir = malloc(sizeof(t_redir));
	if (!redir_node->cmd->redir)
	{
		free(redir_node->cmd);
		free(redir_node->file);
		free(redir_node);
		return NULL;
	}
	redir_node->cmd->redir->file = redir_node->file;
	redir_node->cmd->redir->type = IN;
	redir_node->cmd->redir->next = NULL;

	return redir_node;
}
t_ast_node *create_redirect_out_node(t_ast_node *cmd_node, char *file)
{
	t_ast_node *redir_node = malloc(sizeof(t_ast_node));
	if (!redir_node)
		return NULL;

	redir_node->type = NODE_REDIR_OUT;
	redir_node->left = cmd_node; // Command that writes to the output file
	redir_node->right = NULL;
	redir_node->file = strdup(file); // File to write the output to
	if (!redir_node->file)
	{
		perror("strdup");
		free(redir_node);
		return NULL;
	}
	return redir_node;
}

t_ast_node *create_redirect_append_node(t_ast_node *cmd_node, char *file)
{
	t_ast_node *redir_node = malloc(sizeof(t_ast_node));
	if (!redir_node)
		return NULL;

	redir_node->type = NODE_REDIR_APPEND;
	redir_node->left = cmd_node; // Command that writes to the output file
	redir_node->right = NULL;
	redir_node->file = strdup(file); // File to append the output to

	return redir_node;
}
t_ast_node *create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node *pipe_node = malloc(sizeof(t_ast_node));
	if (!pipe_node)
		return NULL;

	pipe_node->type = NODE_PIPE;
	pipe_node->left = left;	  // Left side of the pipe (command before the pipe)
	pipe_node->right = right; // Right side of the pipe (command after the pipe)
	pipe_node->file = NULL;

	return pipe_node;
}
t_ast_node *create_command_node()
{
	t_ast_node *cmd_node = malloc(sizeof(t_ast_node));
	if (!cmd_node)
		return NULL;

	cmd_node->type = NODE_CMD;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	cmd_node->cmd = malloc(sizeof(t_cmd));
	if (!cmd_node->cmd)
	{
		free(cmd_node);
		return NULL;
	}
	cmd_node->cmd->argv = NULL;
	cmd_node->cmd->next = NULL;
	cmd_node->cmd->redir = NULL;

	return cmd_node;
}
void add_argument_to_command(t_cmd *cmd, char *arg)
{
	int i = 0;

	// Find the current length of argv
	while (cmd->argv && cmd->argv[i])
		i++;

	// Reallocate argv to fit the new argument
	char **new_argv = realloc(cmd->argv, sizeof(char *) * (i + 2));
	if (!new_argv)
		return;

	new_argv[i] = strdup(arg); // Add the new argument
	new_argv[i + 1] = NULL;	   // Ensure argv is NULL-terminated

	cmd->argv = new_argv;
}

t_ast_node *create_heredoc_node(t_ast_node *cmd_node, char *delim)
{
	t_ast_node *redir_node = malloc(sizeof(t_ast_node));
	if (!redir_node)
		return NULL;

	redir_node->type = NODE_HEREDOC;
	redir_node->left = cmd_node; // Command that receives input from the heredoc
	redir_node->right = NULL;
	redir_node->file = strdup(delim); // Delimiter for the heredoc

	return redir_node;
}
