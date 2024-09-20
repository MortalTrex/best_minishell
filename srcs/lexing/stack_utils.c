/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:43 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/17 19:22:28 by mmiilpal         ###   ########.fr       */
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
	t_token	*last;

	last = ft_stacklast(*stack);
	if (!last)
		*stack = new;
	else
		last->next = new;
}

t_token	*ft_stacknew(int type, void *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*ft_stacklast(t_token *stack)
{
	t_token	*tmp;

	if (!stack)
		return (NULL);
	tmp = stack;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_stackclear(t_token **stack)
{
	t_token	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free((*stack)->value);
		free((*stack));
		*stack = tmp;
	}
	*stack = NULL;
}
