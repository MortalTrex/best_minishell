/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/07 15:55:44 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_ast(t_ast_node *node)
{
	if (node == NULL)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

void parse_tokens(t_data *data)
{
	t_ast_node *root = NULL;

	printf("Parsing tokens...\n");
	if (!check_pipe_syntax(data->tok))
		return;
	ft_expand_env_vars(&data->tok);
	if (data->ast != NULL)
		free_ast(data->ast);
	// data->ast = parse(data->tok);
	root = data->ast;
	// printf("AST constructed, printing...\n");
	// print_ast(root, 0);
}
