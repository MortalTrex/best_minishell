/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:51:31 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/30 15:57:27 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool handle_redir(t_redir **redir, t_token **token, t_data *data)
{
	t_redir *tmp;
	t_token_type type;

	if (data->parsing_error)
		return (false);
	if (is_redirection(*token))
	{
		type = (*token)->type;
		*token = (*token)->next;
		if (!*token || (*token)->type != T_WORD)
			return ((data->parsing_error = ERR_SYN), false);
		tmp = ft_create_redir_node(type, (*token)->value);
		if (!tmp)
			return ((data->parsing_error = ERR_MEM), false);
		ft_append_redir(redir, tmp);
		*token = (*token)->next;
	}
	return (true);
}

bool join_words(char **command, t_token **current, t_data *data)
{
	char *tmp;
	char *joined;

	if (data->parsing_error)
		return (false);
	if (!*command)
		*command = ft_strdup("");
	if (!*command)
		return (false);
	while (*current && (*current)->type == T_WORD)
	{
		tmp = *command;
		joined = ft_strjoin(tmp, ft_strcmp(tmp, "") ? " " : "");
		if (!joined)
			return (free(tmp), false);
		free(tmp);
		tmp = joined;
		joined = ft_strjoin(tmp, (*current)->value);
		if (!joined)
			return (free(tmp), false);
		free(tmp);
		*command = joined;
		*current = (*current)->next;
	}
	return (true);
}

t_ast_node *simple_command(t_token **current_token, t_data *data)
{
	t_ast_node *node;

	node = ft_create_node(NODE_CMD);
	if (!node)
		return (data->parsing_error = ERR_MEM, NULL);
	while (*current_token && (*current_token)->type != T_PIPE)
	{
		if ((*current_token)->type == T_WORD)
		{
			if (!join_words(&(node->command), current_token, data))
				return (free_node(node), NULL);
		}
		else if (is_redirection(*current_token))
		{
			if (!handle_redir(&(node->redir), current_token, data))
				return (free(node->command), free(node), NULL);
		}
		else
			*current_token = (*current_token)->next;
	}
	return (node);
}
