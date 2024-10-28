/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:03:55 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/28 13:30:31 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ok
t_ast_node *ft_create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node *pipe_node;

	pipe_node = ft_create_node(NODE_PIPE);

	if (!pipe_node)
		return (NULL); // add error message
	pipe_node->left = left;
	pipe_node->right = right;
	printf("pipe node created");
	return (pipe_node);
}

t_redir *ft_create_redir_node(t_token_type type, char *file)
{
	t_redir *redir;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (free(redir), NULL);
	if (type == T_REDIR_IN)
		redir->type = IN;
	else if (type == T_REDIR_OUT)
		redir->type = OUT;
	else if (type == T_REDIR_APPEND)
		redir->type = D_APPEND;
	else if (type == T_REDIR_HERE)
		redir->type = D_HEREDOC;
	return (redir);
}


t_ast_node *ft_create_node(t_ast_node_type type)
{
	t_ast_node *node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

void ft_append_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir *tmp;

	if (!cmd->redir)
	{
		cmd->redir = redir;
		return ;
	}
	tmp = cmd->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}
