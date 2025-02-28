/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:47:35 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 16:13:14 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		if (str[i])
			i++;
	}
	return (0);
}

static int	valid_expansion(char *str, int i, char *quote)
{
	if (*quote == SQ)
		return (0);
	if (str && is_heredoc(str))
		return (0);
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
			|| str[i + 1] == '?'))
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int	get_quote(char *quote, char c)
{
	if (c == SQ || c == DQ)
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
		return (*quote);
	}
	return (-1);
}

static int	count_dollars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*expanding(char *str, t_data *data)
{
	int		i;
	char	quote;
	int		expansions_counter;

	i = 0;
	quote = 0;
	expansions_counter = count_dollars(str);
	while (str[i])
	{
		get_quote(&quote, str[i]);
		if (valid_expansion(str, i, &quote) && expansions_counter-- > 0)
		{
			str = get_value_after_expansion(str, data, &i);
			if (!str || !str[0])
				break ;
		}
		else
			i++;
	}
	return (str);
}
