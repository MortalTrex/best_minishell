/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:51:31 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/28 17:02:58 by mmiilpal         ###   ########.fr       */
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

bool join_words(char **argv, t_token *token, t_data *data)
{
	t_token *current;

	if (data->error_msg)
		return (false);
	if (!*argv)
		*argv = ft_strdup("");
	if (!*argv)
		return (false);
	current = token;
	if (current->type == T_WORD)
	{
		if (*argv)
			*argv = ft_strjoin(*argv, " ");
		*argv = ft_strjoin(*argv, current->value);
		if (!*argv)
			return (false);
	}
	return (true);
}
// handle parsing errors!!!
t_ast_node *simple_command(t_data *data)
{
	t_ast_node *node;
	t_token *current;

	if (data->error_msg)
		return (NULL);
	current = data->tok;
	node = ft_create_node(NODE_CMD);
	if (!node)
		return (NULL); // add error message
	// Pourquoi une boucle pour une commande simple ?
	while (current && (current->type == T_WORD || is_redirection(current)))
	{
		if (current->type == T_WORD)
		{
			if (!join_words(node->argv, current, data))
				return (NULL);
		}
		else if (is_redirection(current))
		{
			if (!handle_redir(node, current, data))
				return (free(node->argv), free(node), NULL);
		}
		current = current->next;
	}
	printf("created cmd node %s\n", *node->argv);
	data->tok = current;
	return (node);
}
