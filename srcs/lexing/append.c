/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/04 18:02:51 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_append_operator(t_token **tokens, char *line, unsigned int *i)
{
	t_token *new;
	char *operator;

	operator= ft_substr(line, *i, 1);
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
		new = ft_stacknew(T_OPERATOR, operator);
	(*i)++;
	ft_stackadd_back(tokens, new);
}

void ft_substr_append_word(t_token **tokens, char *line, unsigned int start,
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

bool ft_append_word(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int start;
	int len;

	start = *i;
	len = 0;
	while (line[*i] && !ft_is_operator(line[*i + 1]) && !ft_isspace(line[*i]))
	{
		if (ft_is_quote(line[*i]))
		{
			if (!ft_skip_quotes(line, i))
				return (false);
		}
		else
		{
			(*i)++;
			len++;
		}
	}
	ft_substr_append_word(tokens, line, start, len);
	return (true);
}

void ft_append_word_squotes(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int start;
	int len;

	start = *i;
	len = 0;
	(*i)++; // Skip the '\'' character
	while (line[*i] && line[*i] != '\'')
	{
		(*i)++;
		len++;
	}
	ft_substr_append_word(tokens, line, start, len);
	if (line[*i] == '\'')
		(*i)++;
}

void ft_append_word_dquotes(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int start;
	int len;

	start = *i;
	len = 0;
	(*i)++; // Skip the '"' character
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$')
		{
			ft_substr_append_word(tokens, line, start, len);
			ft_append_env_var(tokens, line, i);
			start = *i;
			len = 0;
		}
		else
		{
			(*i)++;
			len++;
		}
	}
	ft_substr_append_word(tokens, line, start, len);
	if (line[*i] == '"')
		(*i)++;
}

void ft_append_env_var(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int start = *i;
	int len = 0;
	char *env_var_name;
	char *env_var_value;
	t_token *new;

	(*i)++; // Skip the '$' character

	// Check if the variable is enclosed in braces
	if (line[*i] == '{')
	{
		(*i)++; // Skip the '{' character
		start = *i;
		while (line[*i] && line[*i] != '}')
		{
			(*i)++;
			len++;
		}
		if (line[*i] == '}')
		{
			(*i)++; // Skip the '}' character
		}
	}
	else
	{
		start = *i;
		while (ft_isalnum(line[*i]) || line[*i] == '_')
		{
			(*i)++;
			len++;
		}
	}

	env_var_name = ft_substr(line, start, len); // Extract the variable name
	if (!env_var_name)
	{
		fprintf(stderr, "Error: ft_substr returned NULL\n");
		return;
	}
	env_var_value = getenv(env_var_name); // Retrieve the environment variable's value
	free(env_var_name);					  // Free the variable name as it's no longer needed
	if (!env_var_value)
	{
		env_var_value = ""; // If the variable is not found, use an empty string
	}
	new = ft_stacknew(T_ENV_VAR, ft_strdup(env_var_value)); // Store the value in the token
	if (!new)
	{
		fprintf(stderr, "Error: ft_stacknew returned NULL\n");
		return;
	}
	ft_stackadd_back(tokens, new);
}
