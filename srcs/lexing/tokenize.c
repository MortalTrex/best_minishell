/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/12 17:53:35 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_detect_builtin(t_token **tok, t_data *data)
{
	t_token	*current;

	current = *tok;
	while (current)
	{
		if (current->type == T_WORD)
		{
			if (!ft_strcmp(current->value, "cd"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "echo"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "pwd"))
			{
				current->type = T_BUILTIN;
				ft_pwd();
			}
			else if (!ft_strcmp(current->value, "export"))
			{
				current->type = T_BUILTIN;
				ft_env(data);
			}
			else if (!ft_strcmp(current->value, "unset"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "env"))
			{
				current->type = T_BUILTIN;
				ft_env(data);
			}
			else if (!ft_strcmp(current->value, "exit"))
				exit(0);
		}
		current = current->next;
	}
}

bool	ft_tokenize(char *line, t_token **tokens, t_data *data)
{
	unsigned int	i;
	bool			is_double_quotes;
	bool			is_single_quotes;
	char			token_buffer[256]; // Buffer for current token
	int				buffer_index;

	i = 0;
	is_double_quotes = true;
	is_single_quotes = true;
	buffer_index = 0;

	while (line[i] != '\0')
	{
		if (ft_isspace(line[i]))
		{
			// If we have a token in the buffer, append it
			if (buffer_index > 0)
			{
				token_buffer[buffer_index] = '\0';
				ft_append_word(tokens, token_buffer);
				buffer_index = 0; // Reset buffer for the next token
			}
			i++;
		}
		else if (line[i] == '"' || line[i] == '\'')
			is_double_quotes = ft_append_word_quotes(token_buffer, &buffer_index, line, &i);
		else if (line[i] == '$')
			ft_append_env_var(tokens, line, &i); // Store env var as part of the token
		else if (ft_is_operator(line[i]))
		{
			// If we have a token in the buffer, append it before the operator
			if (buffer_index > 0)
			{
				token_buffer[buffer_index] = '\0';
				ft_append_word(tokens, token_buffer);
				buffer_index = 0; // Reset buffer
			}
			ft_append_operator(tokens, line, &i); // Handle operator
			if (line[i] != '\0' && ft_is_operator(line[i]))
				return (fprintf(stderr, "Error: Unexpected operator sequence\n"), false);
		}
		else
		{
			// Regular characters get added to the token buffer
			token_buffer[buffer_index++] = line[i++];
		}
	}
	// Append any leftover token in the buffer at the end
	if (buffer_index > 0)
	{
		token_buffer[buffer_index] = '\0';
		ft_append_word(tokens, token_buffer);
	}
	if (is_double_quotes == false || is_single_quotes == false)
		return (ft_msg_free_exit("Error: Unclosed quotes\n", tokens), false);
	ft_detect_builtin(tokens, data);
	// Append an EOF token at the end
	return (ft_stackadd_back(tokens, ft_stacknew(T_EOF, NULL)), true);
}

