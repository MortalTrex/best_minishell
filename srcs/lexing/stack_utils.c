/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:43 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/10 17:09:58 by rbalazs          ###   ########.fr       */
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

t_token	*ft_stacknew(int type, char *value)
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
	t_token	*next;

	if (stack == NULL || *stack == NULL)
		return ;
	tmp = *stack;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = NULL;
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
