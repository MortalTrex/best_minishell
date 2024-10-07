#include "minishell.h"

bool check_pipe_syntax(t_token *token)
{
	t_token *current = token;

	if (current && current->type == T_PIPE)
		return (fprintf(stderr, "Syntax error: unexpected pipe at the beginning\n"), false);
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (!current->next)
				return (fprintf(stderr, "Syntax error: unexpected pipe at the end\n"), false);
			if (current->next && current->next->type == T_PIPE)
				return (fprintf(stderr, "Syntax error: consecutive pipes\n"), false);
			if (current->next && current->next->type != T_WORD)
				return (fprintf(stderr, "Syntax error: pipe not followed by a command\n"), false);
		}
		current = current->next;
	}
	return (true);
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
