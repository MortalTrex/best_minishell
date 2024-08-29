/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2024/08/29 15:10:51 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_append_operator(t_token **tokens, char *line, unsigned int *i)
{
	t_token	*new;

	new = NULL;
	if (line[*i] == '|')
		new = ft_stacknew(T_OPERATOR, &line[*i]);
	else if (line[*i] == ';')
		new = ft_stacknew(T_OPERATOR, &line[*i]);
	else
	{
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
			new = ft_stacknew(T_OPERATOR, &line[*i]);
	}
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

bool	ft_append_word_quotes(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int	start;
	int				len;

	start = *i;
	len = 0;
	while (line[*i] && line[*i] != '"')
	{
		(*i)++;
		len++;
	}
	ft_substr_append_word(tokens, line, start, len);
	return (true);
}
