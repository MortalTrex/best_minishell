/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:50:27 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 16:03:31 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duplicate_fd(int fd, int new_fd, t_data *data, int exit_status)
{
	if (dup2(fd, new_fd) == -1)
	{
		perror("dup2");
		data->exit_status = exit_status;
		ft_free_all_and_exit(data, data->exit_status);
	}
}

void	close_fds(t_data *data)
{
	if (data->infile_fd >= 0)
		close(data->infile_fd);
	if (data->outfile_fd >= 0)
		close(data->outfile_fd);
}

void	close_pipe_fds(t_data *data)
{
	if (data->pipe_fd[0] != -2)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -2)
		close(data->pipe_fd[1]);
}
