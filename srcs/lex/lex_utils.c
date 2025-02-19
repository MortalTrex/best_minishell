/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:56:45 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/19 14:57:52 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_delimiter_quote_status(t_token *token)
{
	int		i;
	t_token	*tmp;

	tmp = token;
	token->quotes = false;
	while (tmp)
	{
		i = 0;
		if (tmp->type == T_DELIMITER)
		{
			while (tmp->value[i])
			{
				if (tmp->value[i] == '\"' || tmp->value[i] == '\'')
					tmp->quotes = true;
				i++;
			}
		}
		tmp = tmp->next;
	}
}