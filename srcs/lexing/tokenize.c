/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/05 17:29:22 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_tokenize(char *line, t_token **tokens)
{
	unsigned int i = 0;
	bool in_double_quotes = false;
	bool in_single_quotes = false;

	while (line[i] != '\0')
	{
		if (line[i] == '"' && !in_single_quotes) // Handle double quotes
		{
			in_double_quotes = !in_double_quotes;
			if (in_double_quotes)
				i++; // Move past the opening double quote
			else if (!ft_handle_quotes(tokens, line, &i, '"'))
				return false;
		}
		else if (line[i] == '\'' && !in_double_quotes) // Handle single quotes
		{
			in_single_quotes = !in_single_quotes;
			if (in_single_quotes)
				i++; // Move past the opening single quote
			else if (!ft_handle_quotes(tokens, line, &i, '\''))
				return false;
		}
		else if (in_double_quotes) // Handle content inside double quotes
		{
			if (!ft_handle_quotes(tokens, line, &i, '"'))
				return false;
		}
		else if (in_single_quotes) // Handle content inside single quotes
		{
			if (!ft_handle_quotes(tokens, line, &i, '\''))
				return false;
		}
		else // Handle regular tokens outside quotes
		{
			if (ft_isspace(line[i]))
				i++; // Skip whitespace
			else if (line[i] == '$')
				ft_append_env_var(tokens, line, &i); // Handle env variables
			else if (ft_is_operator(line[i]))		 // Handle operators
			{
				ft_append_operator(tokens, line, &i);
				if (line[i] != '\0' && ft_is_operator(line[i]))
					return (fprintf(stderr, "Error: Unexpected operator sequence\n"), false);
			}
			else if (!ft_append_word(tokens, line, &i)) // Handle regular words
				return (false);
		}
	}

	if (in_double_quotes || in_single_quotes) // Check for unclosed quotes
		return (ft_msg_free_exit("Error: Unclosed quotes\n", tokens), false);

	return (ft_stackadd_back(tokens, ft_stacknew(T_EOF, NULL)), true);
}

/*
bool ft_tokenize(char *line, t_token **tokens)
{
	unsigned int i;
	bool is_double_quotes;
	bool is_single_quotes;

	i = 0;
	is_double_quotes = false;
	is_single_quotes = false;
	while (line[i] != '\0')
	{
		if (line[i] == '"' && !is_single_quotes)
		{
			is_double_quotes = !is_double_quotes;
			if (is_double_quotes)
				i++;
			else
				ft_append_word_dquotes(tokens, line, &i);
		}
		else if (line[i] == '\'' && !is_double_quotes)
		{
			is_single_quotes = !is_single_quotes;
			if (is_single_quotes)
				i++;
			else
				ft_append_word_squotes(tokens, line, &i);
		}
		else if (is_double_quotes)
		{
			ft_append_word_dquotes(tokens, line, &i);
		}
		else if (is_single_quotes)
		{
			ft_append_word_squotes(tokens, line, &i);
		}
		else
		{
			if (ft_isspace(line[i]))
				i++;
			else if (line[i] == '$')
				ft_append_env_var(tokens, line, &i);
			else if (ft_is_operator(line[i]))
			{
				ft_append_operator(tokens, line, &i);
				if (line[i] != '\0' && ft_is_operator(line[i]))
					return (fprintf(stderr, "Error: Unexpected operator sequence\n"), false);
			}
			else if (!ft_append_word(tokens, line, &i))
				return (false);
		}
	}
	if (is_double_quotes || is_single_quotes)
		return (ft_msg_free_exit("Error: Unclosed quotes\n", tokens), false);
	return (ft_stackadd_back(tokens, ft_stacknew(T_EOF, NULL)), true);
}
 */
