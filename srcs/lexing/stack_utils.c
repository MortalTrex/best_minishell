/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:43 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/15 20:30:38 by rbalazs          ###   ########.fr       */
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


t_token *ft_create_new_token(char *value, t_token_type type)
{
    t_token *new_token;

    new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->value = ft_strdup(value);
    if (!new_token->value)
    {
        free(new_token);
        return (NULL);
    }
    new_token->type = type;
    new_token->next = NULL;
    new_token->prev = NULL;
    return (new_token);
}

void ft_add_node_token(t_token *token, char *value, t_token_type type)
{
    t_token *new_token;

    new_token = ft_create_new_token(value, type);
    if (!new_token)
        return;


    while (token->next)
        token = token->next;

    token->next = new_token;
    new_token->prev = token;
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

void	ft_envclear(t_env *env)
{
	t_env	*temp;
	t_env	*tmp;

	temp = env;
	while (temp)
	{
		free(temp->line);
		free(temp->name);
		free(temp->value);
		tmp = temp->next;
		free(temp);
		temp = tmp;
	}
	env = NULL;
}
