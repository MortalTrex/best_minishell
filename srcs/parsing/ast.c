/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/03 18:54:36 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_ast_node	*create_tree(t_token **current_token, t_data *data)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*current;

	current = *current_token;
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

void	parse_tokens(t_data *data)
{
	if (!check_pipe_syntax(data->tok, data))
		ft_parsing_error(data);
	data->ast = create_tree(&data->tok, data);
	if (data->parsing_error)
		ft_parsing_error(data);
	// if (data->ast != NULL)
	// {
	// 	printf("AST constructed, printing...\n");
	// 	print_ast(data->ast, 0);
	// 	free_ast(&data->ast, data);
	// }
}
