/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:30:01 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 18:17:40 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fds(t_token *redirs, t_data *data)
{
	if (redirs->type == T_REDIR_OUT || redirs->type \
		== T_REDIR_APPEND)
	{
		get_fd_out(redirs, data);
		get_fd_in(redirs, data);
	}
	else
	{
		get_fd_in(redirs, data);
		get_fd_out(redirs, data);
	}
}

void	open_and_redirect_fd(t_cmd *current, t_data *data)
{
	get_fds(current->redirs, data);
	if (data->outfile_fd != -2)
	{
		duplicate_fd(data->outfile_fd, STDOUT_FILENO, data, 1);
		close(data->outfile_fd);
	}
	if (data->infile_fd != -2)
	{
		duplicate_fd(data->infile_fd, STDIN_FILENO, data, 1);
		close(data->infile_fd);
	}
	if (data->heredoc && !current->next)
		unlink_heredoc(data);
}

void	has_no_filename(t_cmd *current, t_data *data, int prev_fd)
{
	if (prev_fd != 0 && data->infile_fd == -2)
	{
		duplicate_fd(prev_fd, STDIN_FILENO, data, 1);
		close(prev_fd);
	}
	if (current->next && data->outfile_fd == -2)
		duplicate_fd(data->pipe_fd[1], STDOUT_FILENO, data, 1);
	close_pipe_fds(data);
}
