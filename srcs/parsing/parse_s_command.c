/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:51:31 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/29 15:47:15 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool handle_redir(t_redir **redir, t_token *token, t_data *data)
{
	t_redir *tmp;

	if (is_redirection(token))
	{
		token = token->next;
		if (!token || token->type != T_WORD)
			return ((data->error_msg = ERR_SYN), false);
		tmp = ft_create_redir_node(token->type, token->value);
		if (!tmp)
			return ((data->error_msg = ERR_MEM), false);
		ft_append_redir(redir, tmp);
	}
	return (true);
}

bool join_words(char **command, t_token *current, t_data *data)
{
	char *tmp;

	if (data->error_msg)
		return (false);
	if (!*command)
		*command = ft_strdup("");
	if (!*command)
		return (false);
	if (current && current->type == T_WORD)
	{
		tmp = current->value;
		if (ft_strcmp(*command, ""))
			tmp = ft_strjoin(" ", tmp);
		*command = ft_strjoin(*command, tmp);
		if (!*command)
			return (free(tmp), false);
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
		return (NULL);
	while (current && (current->type == T_WORD || is_redirection(current)))
	{
		if (current->type == T_WORD)
		{
			if (!join_words(&(node->command), current, data))
				return (free_node(node), NULL);
		}
		else if (is_redirection(current))
		{
			if (!handle_redir(&(node->redir), current, data))
				return (free(node->command), free(node), NULL);
		}
		current = current->next;
	}
	printf("created cmd node %s\n", node->command);
	return (node);
}
