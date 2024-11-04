/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:37:28 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/04 17:36:27 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_exec_pipe_child(t_ast_node *node, int pfds[2], bool isleft, t_data *data)
{
	int	status;

	if (isleft)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	else
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	status = exec_node(node, data, true);
	(ft_free_all(&data), exit(status));
}

int	exec_pipe(t_ast_node *node, t_data *data)
{
	int		fds[2];
	int		left;
	int		right;
	int		status;

	pipe(fds);
	left = fork();
	if (left == -1)
		(perror("fork"), exit(EXIT_FAILURE));
	data->last_pid = left;
	if (!left)
		ft_exec_pipe_child(node->left, data, fds, true);
	else
	{
		right = fork();
		if (right == -1)
			(perror("fork"), exit(EXIT_FAILURE));
		data->last_pid = right;
		if (!right)
			ft_exec_pipe_child(node->right, data, fds, false);
		else
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(left, &status, 0);
			waitpid(right, &status, 0);
			return(status);
		}
	}
	return (ERRGEN);
}

int	exec_node(t_ast_node *node, t_data *data, bool ispipe)
{
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == NODE_PIPE)
		return (exec_pipe(node, data));
	else
		return (exec_onecommand(node, data, ispipe));
	return (ERRGEN);
}

