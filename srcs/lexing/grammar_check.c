/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:22:20 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 18:29:13 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_or_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	valid_quotes(char *str)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == SQ && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == DQ && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (!(in_single_quote || in_double_quote));
}

void	update_token_quote_status(t_token *token)
{
	int		i;
	t_token	*tmp;

	tmp = token;
	token->quotes = 0;
	while (tmp)
	{
		i = 0;
		if (tmp->type == T_DELIMITER)
		{
			while (tmp->value[i])
			{
				if (tmp->value[i] == DQ || tmp->value[i] == SQ)
					tmp->quotes = 1;
				i++;
			}
		}
		tmp = tmp->next;
	}
}

int	len_between_tokens(char *str, int i, char c)
{
	int	j;

	j = i;
	if (str[i] == c)
	{
		while (str[j] == c)
			j++;
		return (j - i);
	}
	return (0);
}

int	len_invalid_type(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i])
		&& (str[i] == '|' || str[i] == '<' || str[i] == '>'))
		i++;
	return (i);
}
