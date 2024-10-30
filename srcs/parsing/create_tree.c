/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:39:59 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/30 15:40:07 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// error message handling

t_ast_node *create_tree(t_token **current_token, t_data *data)
{
	t_ast_node *left;
	t_ast_node *right;
	t_token *current = *current_token;

	if (!current)
		return (NULL);
	left = simple_command(&current, data);
	if (!left)
		return (NULL);
	while (current && current->type == T_PIPE)
	{
		current = current->next;
		if (!current || current->type != T_WORD)
			return (data->parsing_error = ERR_SYN, left);
		right = create_tree(&current, data);
		if (!right)
			return (left);
		left = ft_create_pipe_node(data, left, right);
		if (!left)
			return (free_ast(&left, data), free_ast(&right, data), NULL);
	}
	return (left);
}
