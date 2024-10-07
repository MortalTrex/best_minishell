/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/07 16:47:29 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(t_token *token)
{
	if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT \
			||token->type == T_REDIR_HERE || token->type == T_REDIR_APPEND)
		return (true);
	return (false);
}
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
	t_ast_node *root;

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
