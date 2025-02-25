/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:22:04 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/25 14:28:14 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	free_redir(t_redir **redir)
{
	t_redir	*next;
	t_redir	*tmp;

	if (!redir)
		return ;
	tmp = *redir;
	while (tmp)
	{
		free(tmp->file);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*redir = NULL;
}

void	ft_free_command(t_ast_node *node)
{
	if (!node)
		return ;
	free_redir(&node->redir);
	free(node->command);
	ft_free_tab(node->argv);
}

void	free_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node -> type == NODE_CMD)
		ft_free_command(node);
	else
	{
		if (node->left)
			free_node(node->left);
		if (node->right)
			free_node(node->right);
	}
	free(node);
	node = NULL;
}

void	free_ast(t_ast_node **node, t_data *data)
{
	free_node(*node);
	*node = NULL;
	if (data->tok)
		ft_stackclear(&data->tok);
	data->new_ast = NULL;
}

void free_newast(t_ast_node *node)
{
    t_ast_node *tmp;

    while (node)
    {
        tmp = node->right;
        free(node);
        node = tmp;
    }
}

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return ;
}

void	ft_free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->user_line)
		free(data->user_line);
	if (data->tok)
		ft_stackclear(&data->tok);
	if (data->envc)
		ft_free_tab(data->envc);
	if (data->free_value == 0)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->stdin_backup);
		close(data->stdout_backup);
		if (data->env)
			ft_envclear(&data->env);
	}
	if (data->ast)
		free_ast(&data->ast, data);
	if (data->new_ast)
		free_newast(data->new_ast);
}

void	free_and_exit_shell(t_data *data, int exit_code)
{
	if (data)
	{
		free_data(data);
		if (data->env)
			free_env((data->env));
	}
	rl_clear_history();
	exit(exit_code);
}

void	free_shell(t_data *data)
{
	if (data)
	{
		if (data->heredoc)
		{
			free(data->heredoc);
			data->heredoc = NULL;
		}
		if (data->tokens)
			free_tokens(&(data->tokens));
		if (data->commands)
			free_commands(&(data->commands));
	}
}

void	free_commands(t_cmd **commands)
{
	t_cmd	*temp;
	t_cmd	*current;

	if (!*commands)
		return ;
	current = *commands;
	while (current)
	{
		temp = current->next;
		if (current->cmd_args)
			ft_free_tab(current->cmd_args);
		free_tokens(&(current->redirs));
		free(current);
		current = temp;
	}
	*commands = NULL;
}
void	free_tokens(t_token **tokens)
{
	t_token	*temp;
	t_token	*current;

	if (!*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		temp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
	*tokens = NULL;
}