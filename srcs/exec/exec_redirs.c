/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:30:01 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 14:57:39 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fds(t_token *redirections, t_data *shell)
{
	if (redirections->type == T_REDIR_OUT || redirections->type == T_REDIR_APPEND)
	{
		get_fd_out(redirections, shell);
		get_fd_in(redirections, shell);
	}
	else
	{
		get_fd_in(redirections, shell);
		get_fd_out(redirections, shell);
	}
}

void	open_and_redirect_fd(t_cmd *current, t_data *shell)
{
	get_fds(current->redirs, shell);
	if (shell->infile_fd != -2)
	{
		duplicate_fd(shell->infile_fd, STDIN_FILENO, shell, 1);
		close(shell->infile_fd);
	}
	if (shell->outfile_fd != -2)
	{
		duplicate_fd(shell->outfile_fd, STDOUT_FILENO, shell, 1);
		close(shell->outfile_fd);
	}
	if (shell->heredoc && !current->next)
		unlink_heredoc(shell);
}

void	has_no_filename(t_cmd *current, t_data *shell, int prev_fd)
{
	if (prev_fd != 0 && shell->infile_fd == -2)
	{
		duplicate_fd(prev_fd, STDIN_FILENO, shell, 1);
		close(prev_fd);
	}
	if (current->next && shell->outfile_fd == -2)
		duplicate_fd(shell->pipe_fd[1], STDOUT_FILENO, shell, 1);
	close_pipe_fds(shell);
}
