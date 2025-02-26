/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:45:19 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 14:52:40 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_file_as_fd_in(t_token *redirections, t_data *shell)
{
	t_token	*current;

	current = redirections;
	while (current)
	{
		if (current->next && (current->next->type == T_FILENAME))
		{
			if (current->type == T_REDIR_IN)
			{
				if (shell->infile_fd != -2)
					close(shell->infile_fd);
				shell->infile_fd = open(current->next->value, O_RDONLY);
			}
		}
		if (shell->infile_fd == -1)
		{
			perror(current->next->value);
			shell->exit_status = 1;
			free_and_exit_shell(shell, shell->exit_status);
		}
		current = current->next;
	}
}

void	get_fd_in(t_token *redirections, t_data *shell)
{
	if (shell->heredoc && redirections->type == T_REDIR_HERE)
	{
		if (shell->infile_fd != -2)
			close(shell->infile_fd);
		shell->infile_fd = open(shell->heredoc, O_RDONLY);
	}
	get_file_as_fd_in(redirections, shell);
}

static void	open_outfile(char *filename, t_data *shell, int flags)
{
	if (shell->outfile_fd != -2)
		close(shell->outfile_fd);
	if (flags == T_REDIR_OUT)
		shell->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		shell->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	get_fd_out(t_token *redirections, t_data *shell)
{
	t_token	*current;

	current = redirections;
	while (current)
	{
		if (current->next && current->next->type == T_FILENAME)
		{
			if (current->type == T_REDIR_OUT)
				open_outfile(current->next->value, shell, T_REDIR_OUT);
			else if (current->type == T_REDIR_APPEND)
				open_outfile(current->next->value, shell, T_REDIR_APPEND);
		}
		if (shell->outfile_fd == -1)
		{
			perror(current->next->value);
			shell->exit_status = 1;
			free_and_exit_shell(shell, shell->exit_status);
		}
		current = current->next;
	}
}
