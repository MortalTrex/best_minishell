/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:56:32 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/13 10:44:08 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ft_erase_all_temp_here_doc(t_ast_node *node)
{
	t_redir	*current;

	current = node->redir;
	while (current)
	{
		if (current->type == D_HEREDOC && current->file_here_doc != NULL)
			unlink(current->file_here_doc);
		current = current->next;
	}
}

void	ft_multi_pipe_child(t_ast_node *node, t_data *data)
{
	if (node->argv)
	{
		if (is_builtin(node->argv[0]))
		{
			ft_detect_builtin(node->argv, data);
			ft_free_all(data);
			exit(data->exit_status);
		}
		else
			exec(data, node->argv);
	}
}

void	ft_multi_pipe(t_ast_node *node, t_data *data)
{
	pipe(data->pipe_fd);
	node->pid = fork();
	if (node->pid == -1)
		ft_error(data, "Error forking");
	if (node->pid == 0)
	{
		ft_exec_redirs(node, data);
		ft_multi_pipe_child(node, data);
	}
}

void	builtin_no_pipe(t_ast_node *node, t_data *data)
{
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	ft_exec_redirs(node, data);
	ft_detect_builtin(node->argv, data);
	dup2(data->stdin_backup, STDIN_FILENO);
	close(data->stdin_backup);
	dup2(data->stdout_backup, STDOUT_FILENO);
	close(data->stdout_backup);
}

void	ft_no_pipe(t_ast_node *node, t_data *data)
{
	if (node && node->argv && is_builtin(node->argv[0]))
		builtin_no_pipe(node, data);
	else
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking\n");
		if (node->pid == 0)
		{
			ft_exec_redirs(node, data);
			exec(data, node->argv);
		}
	}
}