/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:51:31 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/28 19:23:04 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool handle_redir(t_ast_node *node, t_token *token, t_data *data)
{
	t_redir *tmp;

	while (is_redirection(token))
	{
		token = token->next;
		if (!token || token->type != T_WORD)
			return ((data->error_msg = ERR_SYN), false);
		tmp = ft_create_redir_node(token->type, token->value);
		if (!tmp)
			return ((data->error_msg = ERR_MEM), false);
		ft_append_redir(&(node->redir), tmp);
		token = token->next;
	}
	return (true);
}

bool join_words(t_ast_node *node, t_token *token, t_data *data)
{
	t_token *current;

	if (data->error_msg)
		return (false);
	if (!node->command)
		node->command = ft_strdup("");
	if (!node->command)
		return (false);
	current = token;
	if (current->type == T_WORD)
	{
		if (node->command)
			node->command = ft_strjoin(node->command, " ");
		node->command = ft_strjoin(node->command, current->value);
		if (!node->command)
			return (false);
	}
	return (true);
}
// handle parsing errors!!!
t_ast_node *simple_command(t_data *data, t_token *current)
{
	t_ast_node *node;

	if (data->error_msg)
		return (NULL);
	node = ft_create_node(NODE_CMD);
	if (!node)
		return (NULL); // add error message
	// Pourquoi une boucle pour une commande simple ?
	while (current && (current->type == T_WORD || is_redirection(current)))
	{
		if (current->type == T_WORD)
		{
			if (!join_words(node, current, data))
				return (NULL);
		}
		else if (is_redirection(current))
		{
			if (!handle_redir(node, current, data))
				return (free(node->argv), free(node), NULL);
		}
		current = current->next;
	}
	data->tok = current;
	printf("created cmd node %s\n", node->command);
	return (node);
}
