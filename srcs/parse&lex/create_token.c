/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:49:07 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/19 13:11:15 by mmiilpal         ###   ########.fr       */
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
t_token	*create_token(char *value, int type, bool quotes)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->quotes = quotes;;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*temp;

	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	new_token->prev = temp;
}