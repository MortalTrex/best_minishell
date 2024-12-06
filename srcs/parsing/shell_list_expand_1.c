/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_list_expand_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/12/06 21:48:14 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_spaces_in_words(t_data *data)
{
	t_token	*current;

	current = data->tok;
	while (current)
	{
		for (size_t i = 0; current->value[i]; i++)
		{
			if (current->value[i] == '\x01')
				current->value[i] = ' ';
		}
		current = current->next;
	}
}

static bool	ft_type_not_to_expand(t_token_type type)
{
	if (type == T_PIPE || type == T_ASSIGN || type == T_REDIR_IN
		|| type == T_REDIR_OUT || type == T_REDIR_APPEND
		|| type == T_REDIR_HERE)
		return (true);
	return (false);
}

static bool	ft_requires_expansion(const char *str)
{
	bool	in_single_quotes;
	bool	in_double_quotes;

	in_single_quotes = false;
	in_double_quotes = false;
	while (*str)
	{
		if (*str == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
		}
		else if (*str == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
		}
		else if (!in_single_quotes && (*str == '$' || *str == '`'
				|| *str == '\\'))
		{
			return (true);
		}
		str++;
	}
	return (false);
}

void	ft_check_if_expand_values(t_data *data)
{
	t_token	*current;

	current = data->tok;
	while (current)
	{
		current->to_expand = false;
		if (ft_type_not_to_expand(current->type))
		{
			current = current->next;
			continue ;
		}
		current->to_expand = ft_requires_expansion(current->value);
		current = current->next;
	}
}
