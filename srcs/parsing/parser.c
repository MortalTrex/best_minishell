#include "minishell.h"

t_ast_node	*parse_command(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	if (token && token->type == T_WORD)
	{
		*tokens = token->next;
		return (create_ast_node(NODE_COMMAND, token->value));
	}
	return (NULL);
}

t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_ast_node	*left;
	t_token		*token;
	t_ast_node	*right;
	t_ast_node	*node;

	left = parse_command(tokens);
	token = *tokens;
	while (left && token && token->type == T_OPERATOR)
	{
		if (strcmp(token->value, "|") == 0)
		{
			*tokens = token->next;
			right = parse_pipeline(tokens);
			if (right)
			{
				node = create_ast_node(NODE_PIPE, NULL);
				node->left = left;
				node->right = right;
				left = node;
			}
			else
			{
				free_ast(left);
				return (NULL);
			}
		}
		else if (strcmp(token->value, "<<") == 0)
		{
			*tokens = token->next;
			right = parse_command(tokens);
			if (right)
			{
				node = create_ast_node(NODE_REDIRECT, token->value);
				node->left = left;
				node->right = right;
				left = node;
			}
			else
			{
				free_ast(left);
				return (NULL);
			}
		}
		token = *tokens;
	}
	return (left);
}

void	ft_expand_env_vars(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;
	char	*env_var_value;
	char	*new_value;
	char	*env_var_name;

	current = *tokens;
	prev = NULL;
	(void)prev;
	while (current)
	{
		if (current->type == T_WORD && current->value[0] == '$')
		{
			env_var_name = current->value + 1;
			env_var_value = getenv(env_var_name);
			if (env_var_value)
			{
				new_value = strdup(env_var_value);
				if (!new_value)
				{
					fprintf(stderr, "Error: strdup failed to allocate memory\n");
					return ;
				}
				free(current->value);
				current->value = new_value;
			}
			else
			{
				free(current->value);
				current->value = strdup("default_value");
				if (!current->value)
				{
					fprintf(stderr, "Error: strdup failed to allocate memory\n");
					return ;
				}
			}
		}
		prev = current;
		current = current->next;
	}
}

t_ast_node	*parse_sequence(t_token **tokens)
{
	t_ast_node	*left;
	t_token		*token;
	t_ast_node	*right;
	t_ast_node	*node;

	left = parse_pipeline(tokens);
	token = *tokens;
	while (left && token && token->type == T_OPERATOR && strcmp(token->value, ";") == 0)
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
