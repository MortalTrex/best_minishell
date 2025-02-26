/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:53:49 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 18:29:13 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirections(t_token *tokens, t_cmd *command)
{
	t_token	*temp;
	t_token	*redirections;
	t_token	*next;

	redirections = NULL;
	temp = tokens;
	next = NULL;
	if (temp->type == T_PIPE && temp->next)
		temp = temp->next;
	while (temp && temp->type != T_PIPE)
	{
		if (temp->next && temp->type >= T_REDIR_IN && \
			temp->type <= T_REDIR_HERE)
		{
			next = temp->next->next;
			add_token_back(&redirections, create_token(temp->value,
					temp->type, temp->quotes));
			add_token_back(&redirections, create_token(temp->next->value,
					temp->next->type, temp->next->quotes));
			temp = next;
		}
		else
			temp = temp->next;
	}
	command->redirs = redirections;
}
