/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:30:01 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 13:31:07 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fds(t_token *redirections, t_shell *shell)
{
	if (redirections->type == GREAT || redirections->type == GREATGREAT)
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

void	open_and_redirect_fd(t_command *current, t_shell *shell)
{
	get_fds(current->redirections, shell);
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

void	has_no_filename(t_command *current, t_shell *shell, int prev_fd)
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
