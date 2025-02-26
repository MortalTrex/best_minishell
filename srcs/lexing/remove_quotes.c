/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:05:24 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 18:32:36 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*unquote_string(char *str)
{
	char	*new_str;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (get_quote(&quote, str[i]) && str[i] != quote)
			new_str[j++] = str[i];
		i++;
	}
	return (new_str);
}

static char	*delete_char_from_string(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], ft_strlen(str) - i);
		}
		i++;
	}
	return (str);
}

static void	clear_dollar_token(t_token **token)
{
	int	i;

	i = 0;
	if ((*token)->value == NULL)
		return ;
	while ((*token)->value[i])
	{
		if ((*token)->value[0] == '$' && (*token)->value[i + 1]
			&& ((*token)->value[i + 1] == DQ || (*token)->value[i
					+ 1] == SQ))
			(*token)->value = delete_char_from_string((*token)->value, '$');
		i++;
	}
}

void	remove_quotes(t_token *tokens)
{
	t_token	*temp;
	char	*unquoted_value;

	temp = tokens;
	while (temp)
	{
		if (temp->value)
		{
			clear_dollar_token(&temp);
			unquoted_value = unquote_string(temp->value);
			if (unquoted_value)
			{
				free(temp->value);
				temp->value = unquoted_value;
			}
		}
		temp = temp->next;
	}
}
