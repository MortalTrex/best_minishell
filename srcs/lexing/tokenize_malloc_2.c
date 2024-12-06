/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_malloc_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 21:18:17 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	current = *tokens;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->value);
		free(temp);
	}
	*tokens = NULL;
}

t_token_type	ft_identify_type_of_word(char *word)
{
	if (ft_strcmp(word, "|") == 0)
		return (T_PIPE);
	else if (ft_strcmp(word, "<") == 0)
		return (T_REDIR_IN);
	else if (ft_strcmp(word, ">") == 0)
		return (T_REDIR_OUT);
	else if (ft_strcmp(word, ">>") == 0)
		return (T_REDIR_APPEND);
	else if (ft_strcmp(word, "<<") == 0)
		return (T_REDIR_HERE);
	return (T_ARG);
}
