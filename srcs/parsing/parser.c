#include "minishell.h"

bool is_operator(t_token_type type)
{
	return (type == T_PIPE || type == T_REDIR_IN || type == T_REDIR_OUT ||
			type == T_REDIR_APPEND || type == T_REDIR_HERE);
}

t_ast_node *parse_expression(t_token **tokens)
{
	t_ast_node *left = parse_command(tokens);

	// If the current token is an operator (like pipe or redirection)
	while (*tokens && is_operator((*tokens)->type))
	{
		t_token *operator_token = *tokens;
		*tokens = (*tokens)->next;

		// Handle pipe operator
		if (operator_token->type == T_PIPE)
		{
			t_ast_node *right = parse_command(tokens);
			left = create_pipe_node(left, right); // Create pipe node
		}
		else
		{
			// Handle redirection
			left = parse_redirection(left, operator_token, tokens);
		}
	}

	return left;
}
t_ast_node *parse_command(t_token **tokens)
{
	t_ast_node *node = create_command_node();

	// Add arguments to the command
	while (*tokens && ((*tokens)->type == T_WORD || (*tokens)->type == T_BUILTIN))
	{
		add_argument_to_command(node->cmd, (*tokens)->value);
		*tokens = (*tokens)->next;
	}

	return node;
}
t_ast_node *parse_redirection(t_ast_node *command_node, t_token *operator_token, t_token **tokens)
{
	t_ast_node *redir_node = NULL;

	if (*tokens && (*tokens)->type == T_WORD)
	{
		char *file = (*tokens)->value;
		*tokens = (*tokens)->next;

		if (operator_token->type == T_REDIR_IN)
			redir_node = create_redirect_in_node(command_node, file);
		else if (operator_token->type == T_REDIR_OUT)
			redir_node = create_redirect_out_node(command_node, file);
		else if (operator_token->type == T_REDIR_APPEND)
			redir_node = create_redirect_append_node(command_node, file);
		else if (operator_token->type == T_REDIR_HERE)
			redir_node = create_heredoc_node(command_node, file);
	}
	else
	{
		// Handle syntax error: expected file after redirection operator
		fprintf(stderr, "Syntax error: expected file after redirection\n");
	}

	return redir_node;
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
	printf("all good with expand env vars\n");
}
