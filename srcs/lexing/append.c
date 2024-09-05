/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/05 14:18:59 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_append_operator(t_token **tokens, char *line, unsigned int *i)
{
	t_token	*new;
	char	*operator;

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

void	ft_substr_append_word(t_token **tokens, char *line, unsigned int start,
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

bool	ft_append_word(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int	start;
	int				len;

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

void	ft_append_word_squotes(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int	start;
	int				len;

	start = *i;
	len = 0;
	while (line[*i] && line[*i] != '\'')
	{
		(*i)++;
		len++;
	}
	ft_substr_append_word(tokens, line, start, len);
}

void	ft_append_word_dquotes(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int	start;
	int				len;

	start = *i;
	len = 0;
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$')
		{
			if (len > 0)
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
	if (len > 0)
		ft_substr_append_word(tokens, line, start, len);
}


void	ft_append_env_var(t_token **tokens, char *line, unsigned int *i)
{
	int		len;
	char	*env_var_name;

	unsigned int start = *i + 1; // Skip the '$' character
	len = 0;
	while (line[start + len] && (ft_isalnum(line[start + len]) || line[start
			+ len] == '_'))
	{
		len++;
	}
	env_var_name = ft_substr(line, start, len);
	char *env_var_value = getenv(env_var_name);
		// Or use your own function to get the env var value
	free(env_var_name);
	if (env_var_value)
	{
		ft_substr_append_word(tokens, env_var_value, 0,
			ft_strlen(env_var_value));
	}
	*i = start + len; // Advance the index past the environment variable
}
