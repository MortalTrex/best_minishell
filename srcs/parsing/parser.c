#include "minishell.h"

t_ast_node *parse_command(t_token **tokens)
{
	if (!*tokens || (*tokens)->type != T_WORD)
		return (NULL);

	// Create a command node
	t_ast_node *cmd_node = create_ast_node(NODE_COMMAND, (*tokens)->value);
	(*tokens) = (*tokens)->next;

	// Handle redirection operators like '>' or '<'
	while (*tokens && ((*tokens)->type == T_REDIR_IN || (*tokens)->type == T_REDIR_OUT))
	{
		t_ast_node *redir_node = create_ast_node((*tokens)->type == T_REDIR_IN ? NODE_REDIRECT_IN : NODE_REDIRECT_OUT, NULL);
		(*tokens) = (*tokens)->next; // Move to the next token (should be the file for redirection)
		if (!*tokens || (*tokens)->type != T_WORD)
		{
			free_ast(cmd_node);
			free_ast(redir_node);
			return (NULL); // Error: expected a file after redirection
		}
		redir_node->value = strdup((*tokens)->value); // Store the file name
		(*tokens) = (*tokens)->next;

		// Attach the redirection node to the command
		if (!cmd_node->left)
			cmd_node->left = redir_node;
		else
			cmd_node->right = redir_node;
	}

	return (cmd_node);
}

t_ast_node *parse_pipeline(t_token **tokens)
{
	t_ast_node *left_cmd = parse_command(tokens);
	if (!left_cmd)
		return (NULL);

	// If we encounter a pipe after a command
	if ((*tokens)->type == T_PIPE)
	{
		(*tokens) = (*tokens)->next; // Move to the next token after the pipe
		t_ast_node *right_cmd = parse_pipeline(tokens);
		if (!right_cmd)
		{
			free_ast(left_cmd);
			return (NULL);
		}
		t_ast_node *pipe_node = create_ast_node(NODE_PIPE, "|");
		pipe_node->left = left_cmd;
		pipe_node->right = right_cmd;
		return (pipe_node);
	}

	return (left_cmd); // Return the single command if no pipe was found
}

void ft_expand_env_vars(t_token **tokens)
{
	t_token *current = *tokens;

	while (current)
	{
		if (current->type == T_ENV_VAR)
		{
			char *env_value = getenv(current->value + 1); // Skip the '$'
			if (env_value)
			{
				printf("Expanding %s to %s\n", current->value, env_value);
				free(current->value);				// Free old value
				current->value = strdup(env_value); // Replace with expanded value
			}
			else
			{
				printf("Environment variable %s not found.\n", current->value);
				current->value = strdup(""); // Set to an empty string
			}
		}
		current = current->next;
	}
}
