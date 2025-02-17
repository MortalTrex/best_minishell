/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:49:07 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/17 16:51:08 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_not_null_tokens(t_token *tokens)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = tokens;
	if (temp->type == T_PIPE)
		temp = temp->next;
	while (temp && temp->type != T_PIPE)
	{
		if (temp->value)
			count++;
		temp = temp->next;
	}
	return (count);
}