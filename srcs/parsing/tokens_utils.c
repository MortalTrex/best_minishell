/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/25 15:46:35 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_pipe(t_token *token)
{
	if (!token)
		return (NULL);
	while (token)
	{
		if (token->type == PIPE)
			return (token);
		token = token->next;
	}
	return (NULL);
}

int	count_not_null_tokens(t_token *tokens)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = tokens;
	if (temp->type == PIPE)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		if (temp->value)
			count++;
		temp = temp->next;
	}
	return (count);
}

