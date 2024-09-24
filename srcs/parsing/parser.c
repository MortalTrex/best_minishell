#include "minishell.h"

t_ast_node *parse_command(t_token **tokens)
{
	t_token *token = *tokens;

	// Handle T_WORD, T_BUILTIN, and T_ENV_VAR tokens as command nodes
	if (token && (token->type == T_WORD || token->type == T_BUILTIN || token->type == T_ENV_VAR))
	{
		*tokens = token->next;
		return create_ast_node(NODE_COMMAND, token->value);
	}
	return NULL;
}

t_ast_node *parse_pipeline(t_token **tokens)
{
	t_ast_node *left = parse_command(tokens);
	t_token *token = *tokens;

	// Debugging
	if (left)
		printf("Parsed command: %s\n", left->value);
	else
		printf("No command parsed.\n");

	while (left && token && token->type == T_OPERATOR)
	{
		if (strcmp(token->value, "|") == 0)
		{
			*tokens = token->next;
			t_ast_node *right = parse_pipeline(tokens);
			if (right)
			{
				t_ast_node *node = create_ast_node(NODE_PIPE, NULL);
				node->left = left;
				node->right = right;
				left = node;
			}
			else
			{
				free_ast(left);
				return NULL;
			}
		}
		token = *tokens;
	}
	return left;
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

t_ast_node *parse_sequence(t_token **tokens)
{
	t_ast_node *left;
	t_token *token;
	t_ast_node *right;
	t_ast_node *node;

	left = parse_pipeline(tokens);
	token = *tokens;
	while (left && token && token->type == T_OPERATOR)
	{
		*tokens = token->next;
		right = parse_pipeline(tokens);
		if (right)
		{
			node = create_ast_node(NODE_SEQUENCE, NULL);
			node->left = left;
			node->right = right;
			left = node;
		}
		else
		{
			free_ast(left);
			return (NULL);
		}
		token = *tokens;
	}
	return (left);
}
