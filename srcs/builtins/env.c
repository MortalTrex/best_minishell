/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:12 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/03 17:18:53 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *new_node_env(char *line)
{
	t_env *new_node = malloc(sizeof(t_env));
	new_node->line = ft_strdup(line);
	new_node->next = NULL;
	return new_node;
}

void push_node_to_env(t_data *data, char *line)
{
	t_env *new_node;
	t_env *current;

	new_node = new_node_env(line);
	current = data->env;
	if (data->env == NULL)
		data->env = new_node;
	else
	{
		current = data->env;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}
void ft_env(t_data *data)
{
	while (data->env)
	{
		ft_printf("%s\n", data->env->line);
		data->env = data->env->next;
	}
}
