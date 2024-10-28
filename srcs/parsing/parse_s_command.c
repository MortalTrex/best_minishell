/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:51:31 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/28 15:07:58 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool handle_redir(t_cmd *cmd, t_data *data)
{
	t_redir *tmp;

	while (is_redirection(data->tok))
	{
		data->tok = data->tok->next;
		if (!data->tok || data->tok->type != T_WORD)
			return ((data->error_msg = ERR_SYN), false);
		tmp = ft_create_redir_node(data->tok->type, data->tok->value);
		if (!tmp)
			return ((data->error_msg = ERR_MEM), false);
		ft_append_redir(cmd, tmp);
		data->tok = data->tok->next;
	}
	return (true);
}

static t_cmd *ft_create_cmd_node()
{
	t_cmd *cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	return (cmd);
}

bool join_words(char **argv, t_token *token, t_data *data)
{
	printf("JE SUIS DANS JOIN WORDS\n");
	t_token *current;

	if (data->error_msg)
		return (false);
	if (!*argv)
	{
	    *argv = ft_strdup("");
	}
	else
	{
	    *argv = ft_strjoin(*argv, " ");
	}
	if (!*argv)
	    return (false);
	current = token;
	if (current->type == T_WORD)
	{
	    printf("token value is: %s\n", current->value);
	    *argv = ft_strjoin(*argv, current->value);
	    if (!*argv)
			return(false);
		printf("current cmd is:%s\n", *argv);
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
		return (NULL);
	while (current && (current->type == T_WORD || is_redirection(current)))
	{
		if (current->type == T_WORD)
		{
			if (!node->cmd)
			{
				node->cmd = ft_create_cmd_node();
				node->cmd->argv = (char **)ft_calloc(1, sizeof(char *));
			}
			if (!join_words(node->cmd->argv, current, data))
				return (NULL);
		}
		// else if (is_redirection(data->tok))
		// {
		//     if (!handle_redir(node->cmd, data))
		//         return (free(node->cmd->argv), free(node), NULL);
		// }
		current = current->next;
	}
	return (node);
}
