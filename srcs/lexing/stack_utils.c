/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:43 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/23 10:35:02 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void ft_envclear(t_env *env)
{
	t_env *tmp;
	
	while(env)
	{
		tmp = env;
		env = env->next;
		free(tmp->line);
		free(tmp);
	}
}
