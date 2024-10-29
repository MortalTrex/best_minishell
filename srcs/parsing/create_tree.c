/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:39:59 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/29 16:18:17 by mmiilpal         ###   ########.fr       */
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
			return (data->error_msg = ERR_SYN, left);

		right = simple_command(&current, data);
		if (!right)
			return (left);

		left = ft_create_pipe_node(left, right);
		if (!left)
			return (free_ast(&left, data), free_ast(&right, data), NULL);
	}

	*current_token = current; // Update the token list pointer
	return (left);
}
