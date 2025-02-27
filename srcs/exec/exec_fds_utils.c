/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:50:27 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/27 15:49:49 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duplicate_fd(int fd, int new_fd, t_data *shell, int exit_status)
{
	if (dup2(fd, new_fd) == -1)
	{
		perror("dup2");
		shell->exit_status = exit_status;
		ft_free_all_and_exit(shell, shell->exit_status);
	}
}

void	close_fds(t_data *shell)
{
	if (shell->infile_fd >= 0)
		close(shell->infile_fd);
	if (shell->outfile_fd >= 0)
		close(shell->outfile_fd);
}

void	close_pipe_fds(t_data *shell)
{
	if (shell->pipe_fd[0] != -2)
		close(shell->pipe_fd[0]);
	if (shell->pipe_fd[1] != -2)
		close(shell->pipe_fd[1]);
}
