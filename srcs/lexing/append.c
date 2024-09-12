/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/12 15:17:47 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_append_operator(t_token **tokens, char *line, unsigned int *i)
{
	t_token	*new;
	char	*operator;

	operator = ft_substr(line, *i, 1);  // Get the single operator character
	new = NULL;

	if (line[*i + 1] == '>' && line[*i] == '>')
	{
		new = ft_stacknew(T_OPERATOR, ">>");
		(*i)++;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		new = ft_stacknew(T_OPERATOR, "<<");
		(*i)++;
	}
	else
	{
		new = ft_stacknew(T_OPERATOR, operator);  // Single operator
	}

	free(operator);  // Free the temporary substr
	(*i)++;          // Move index forward

	// Add the new token to the token list
	ft_stackadd_back(tokens, new);
}


void	ft_word_to_token(t_token **tokens, char *line, unsigned int start,
		int len)
{
	char	*substr;
	t_token	*new;

	substr = ft_substr(line, start, len);
	if (!substr)
	{
		fprintf(stderr, "Error: ft_substr returned NULL\n");
		return ;
	}
	new = ft_stacknew(T_WORD, substr);
	if (!new)
	{
		free(substr);
		fprintf(stderr, "Error: ft_stacknew returned NULL\n");
		return ;
	}
	ft_stackadd_back(tokens, new);
}

bool	ft_append_word(t_token **tokens, char *token_buffer)
{
	t_token	*new;
	char	*word;

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


bool	ft_append_word_dquotes(char *token_buffer, int *buffer_index, char *line, unsigned int *i)
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

bool	ft_append_word_squotes(char *token_buffer, int *buffer_index, char *line, unsigned int *i)
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

void	ft_append_env_var(t_token **tokens, char *token_buffer, int *buffer_index, char *line, unsigned int *i)
{
	unsigned int	start;
	int				len;
	char			*env_var_name;
	char			*env_var_value;

	start = *i + 1; // Skip the '$' character
	len = 0;

	// Accumulate the environment variable name into the token buffer
	while (line[start + len] && (ft_isalnum(line[start + len]) || line[start + len] == '_'))
	{
		token_buffer[(*buffer_index)++] = line[start + len];
		len++;
	}

	// Null-terminate the environment variable name
	token_buffer[*buffer_index] = '\0';

	// Retrieve the environment variable's value
	env_var_name = strdup(token_buffer);
	if (!env_var_name)
	{
		fprintf(stderr, "Error: strdup failed to allocate memory\n");
		return;
	}
	env_var_value = getenv(env_var_name);
	free(env_var_name);

	if (env_var_value)
	{
		// Append the environment variable value to the token list
		if (!ft_append_word(tokens, env_var_value))
		{
			fprintf(stderr, "Error: ft_append_word failed\n");
			return;
		}
	}

	// Update the index to move past the environment variable
	*i = start + len;
}



