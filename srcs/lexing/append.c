/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/12 16:19:46 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_append_operator(t_token **tokens, char *line, unsigned int *i)
{
	t_token *new_token = malloc(sizeof(t_token));
	if (!new_token)
		return;

	new_token->type = T_OPERATOR;

	// Check for multi-character operators first
	if (ft_is_multi_char_operator(&line[*i]))
	{
		new_token->value = strndup(&line[*i], 2); // Allocate 2 characters for multi-character operators
		(*i) += 2;								  // Move index by 2
	}
	else
	{
		new_token->value = strndup(&line[*i], 1); // Allocate 1 character for single-character operators
		(*i)++;									  // Move index by 1
	}

	new_token->next = NULL;
	ft_stackadd_back(tokens, new_token);
}

void ft_word_to_token(t_token **tokens, char *line, unsigned int start,
					  int len)
{
	char *substr;
	t_token *new;

	substr = ft_substr(line, start, len);
	if (!substr)
	{
		fprintf(stderr, "Error: ft_substr returned NULL\n");
		return;
	}
	new = ft_stacknew(T_WORD, substr);
	if (!new)
	{
		free(substr);
		fprintf(stderr, "Error: ft_stacknew returned NULL\n");
		return;
	}
	ft_stackadd_back(tokens, new);
}

bool ft_append_word(t_token **tokens, char *token_buffer)
{
	t_token *new;
	char *word;

	// If the buffer is empty, return false (no word to append)
	if (!token_buffer || token_buffer[0] == '\0')
		return false;

	// Duplicate the buffer content to use as the token's value
	word = strdup(token_buffer);
	if (!word)
	{
		fprintf(stderr, "Error: strdup failed to allocate memory\n");
		return false;
	}

	// Create a new token with the type T_WORD
	new = ft_stacknew(T_WORD, word);
	if (!new)
	{
		free(word);
		fprintf(stderr, "Error: ft_stacknew returned NULL\n");
		return false;
	}

	// Add the new token to the end of the tokens list
	ft_stackadd_back(tokens, new);
	return true;
}

bool ft_append_word_dquotes(char *token_buffer, int *buffer_index, char *line, unsigned int *i)
{
	(*i)++; // Skip the opening double quote
	while (line[*i] != '"' && line[*i] != '\0')
	{
		token_buffer[(*buffer_index)++] = line[(*i)++];
	}
	if (line[*i] == '"')
		(*i)++; // Skip the closing double quote
	else
		return false; // Unclosed double quote
	return true;
}

bool ft_append_word_squotes(char *token_buffer, int *buffer_index, char *line, unsigned int *i)
{
	(*i)++; // Skip the opening single quote
	while (line[*i] != '\'' && line[*i] != '\0')
	{
		token_buffer[(*buffer_index)++] = line[(*i)++];
	}
	if (line[*i] == '\'')
		(*i)++; // Skip the closing single quote
	else
		return false; // Unclosed single quote
	return true;
}

void ft_append_env_var(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int start;
	unsigned int len;
	char *env_var_name;
	t_token *new_token;

	start = *i; // Skip the '$' character
	len = 1;

	// Find the length of the environment variable name
	while (line[start + len] && (ft_isalnum(line[start + len]) || line[start + len] == '_'))
	{
		len++;
	}

	// Extract the environment variable name
	env_var_name = ft_substr(line, start, len);
	if (!env_var_name)
	{
		fprintf(stderr, "Error: ft_substr failed to allocate memory\n");
		return;
	}

	// Create a new token for the environment variable
	new_token = ft_stacknew(T_ENV_VAR, env_var_name);
	if (!new_token)
	{
		free(env_var_name);
		fprintf(stderr, "Error: ft_stacknew failed to allocate memory\n");
		return;
	}

	// Add the new token to the token list
	ft_stackadd_back(tokens, new_token);

	// Update the index to move past the environment variable
	*i = start + len;
}
