/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:58:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/08 16:36:27 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *parse_command(t_data *data)
{
	t_ast_node *cmd_node;

	// Allocate memory for a new AST node
	cmd_node = create_cmd_node();

	// Parse the command arguments (T_WORD tokens)
	while (data->tok && (data->tok->type == T_WORD || data->tok->type == T_BUILTIN))
	{
		add_to_argv(cmd_node->cmd, data->tok->value);
		data->tok = data->tok->next;
	}

	// Parse any redirections
	while (data->tok && is_redirection(data->tok))
	{
		t_redir *redir = parse_redirection(data);
		add_redir_to_cmd(cmd_node->cmd, redir);
	}

	return cmd_node;
}

t_redir *parse_redirection(t_data *data)
{
	t_redir *redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	// Check the type of redirection and set accordingly
	if (data->tok->type == T_REDIR_IN)
		redir->type = IN;
	else if (data->tok->type == T_REDIR_OUT)
		redir->type = OUT;
	else if (data->tok->type == T_REDIR_APPEND)
		redir->type = D_OUT;
	else if (data->tok->type == T_REDIR_HERE)
		redir->type = D_IN;

	// Set the file from the next token (T_WORD)
	data->tok = data->tok->next; // Move to the file name token
	redir->file = ft_strdup(data->tok->value);

	// Move to the next token after the redirection
	data->tok = data->tok->next;

	redir->next = NULL;
	return redir;
}

t_ast_node *parse_pipe_sequence(t_data *data)
{
	t_ast_node *left = parse_command(data); // Parse the first command

	while (data->tok && data->tok->type == T_PIPE)
	{
		// Create a new pipe node
		t_ast_node *pipe_node = create_pipe_node();

		// Set the left child to the previously parsed command
		pipe_node->left = left;

		// Move to the next token after the pipe
		data->tok = data->tok->next;

		// Parse the command on the right side of the pipe
		pipe_node->right = parse_command(data);

		// Update left for the next pipe, if any
		left = pipe_node;
	}

	return left; // Return the full AST with all pipes and commands
}
