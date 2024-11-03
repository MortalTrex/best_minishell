/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:37:28 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/03 21:29:29 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_ast_node *node, t_data *data)
{
	pid_t	pid;
	int		left;
	int		right;

	g_signals.child_signal = true;

	if (pipe(data->fd) == -1)
		ft_close_fd(data, "Error creating pipe\n");
	pid = fork();
	if (pid == -1)
		ft_close_fd(data, "Error forking\n");
	if (pid == 0)
		ft_process_infile(cmd1, data, true);
	if (pid != 0)
		ft_process_outfile(cmd2, data);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

int	exec_onecommand(t_ast_node *node, t_data *data)
{
	pid_t	pid;

	if (pipe(data->fd) == -1)
		ft_close_fd(data, "Error creating pipe\n");
	pid = fork();
	if (pid == -1)
		ft_close_fd(data, "Error forking\n");
	if (pid == 0)
		ft_process_infile(cmd, data, false);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

int	execute_node(t_ast_node *node, t_data *data)
{
	if (!node)
		return (EXIT_FAILURE);
	if (node->type == NODE_PIPE)
		return (exec_pipe(node, node->right->command, data));
	else
		return (exec_onecommand(node, data));
	return (ENOMEM);
}

