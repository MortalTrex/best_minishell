/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:43 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/09 16:24:59 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_stackadd_back(t_token **stack, t_token *new)
{
	t_token	*curr_node;

	if (!*stack)
	{
		*stack = new;
		return ;
	}
	curr_node = *stack;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new;
	new->prev = curr_node;
}

t_token	*ft_stacknew(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

void	ft_stackclear(t_token **stack)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *stack;
	if (!tmp)
		return ;
	while (tmp)
	{
		free(tmp->value);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*stack = NULL;
}

void	ft_envclear(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->line);
		free(temp);
	}
	*env = NULL;
}
