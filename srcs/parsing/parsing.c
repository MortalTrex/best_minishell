/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:58:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/14 20:08:29 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command(t_data *data)
{
	t_ast_node	*cmd_node;
	t_token		*tmp;
	t_redir		*redir;

	tmp = data->tok;
	cmd_node = create_cmd_node();
	while (tmp && (tmp->type == T_WORD || tmp->type == T_BUILTIN))
	{
		printf("Parsing command: %s\n", tmp->value);
		add_to_argv(cmd_node->cmd, tmp->value, data);
		tmp = tmp->next;
	}
	while (tmp && is_redirection(tmp))
	{
		redir = parse_redirection(data);
		add_redir_to_cmd(cmd_node->cmd, redir);
	}
	return (cmd_node);
}

t_redir	*parse_redirection(t_data *data)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (data->tok->type == T_REDIR_IN)
		redir->type = IN;
	else if (data->tok->type == T_REDIR_OUT)
		redir->type = OUT;
	else if (data->tok->type == T_REDIR_APPEND)
		redir->type = D_OUT;
	else if (data->tok->type == T_REDIR_HERE)
		redir->type = D_IN;
	data->tok = data->tok->next;
	redir->file = ft_strdup(data->tok->value);
	data->tok = data->tok->next;
	redir->next = NULL;
	return (redir);
}

t_ast_node	*parse_pipe_sequence(t_data *data)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;

	left = parse_command(data);
	while (data->tok && data->tok->type == T_PIPE)
	{
		pipe_node = create_pipe_node();
		pipe_node->left = left;
		data->tok = data->tok->next;
		pipe_node->right = parse_command(data);
		left = pipe_node;
	}
	return (left);
}
