/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:52 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/30 19:15:41 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

bool	ft_is_multi_char_operator(const char *str)
{
	return (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0);
}

bool	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

bool	ft_skip_quotes(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

bool	ft_is_wordchar(char c)

{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

bool	ft_is_separator(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t'
		|| *s == '<' || *s == '>' || *s == '|' || *s == '(' || *s == ')')
		return (true);
	return (false);
}


