/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:45:19 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 16:04:04 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_infile(char *filename, t_data *data)
{
	if (data->infile_fd != -2)
		close(data->infile_fd);
	data->infile_fd = open(filename, O_RDONLY);
	if (data->infile_fd == -1)
	{
		perror(filename);
		data->exit_status = 1;
		ft_free_all_and_exit(data, data->exit_status);
	}
}

static void	get_file_as_fd_in(t_token *redirections, t_data *data)
{
	t_token	*current;

	current = redirections;
	while (current)
	{
		if (current->next && current->next->type == T_FILENAME && \
			current->type == T_REDIR_IN)
			open_infile(current->next->value, data);
		current = current->next;
	}
}

void	get_fd_in(t_token *redirections, t_data *data)
{
	if (data->heredoc && redirections->type == T_REDIR_HERE)
	{
		if (data->infile_fd != -2)
			close(data->infile_fd);
		data->infile_fd = open(data->heredoc, O_RDONLY);
		if (data->infile_fd == -1)
		{
			perror(data->heredoc);
			data->exit_status = 1;
			ft_free_all_and_exit(data, data->exit_status);
		}
	}
	get_file_as_fd_in(redirections, data);
}

static void	open_outfile(char *filename, t_data *data, int flags)
{
	if (data->outfile_fd != -2)
		close(data->outfile_fd);
	if (flags == T_REDIR_OUT)
		data->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		data->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->outfile_fd == -1)
	{
		perror(filename);
		data->exit_status = 1;
		ft_free_all_and_exit(data, data->exit_status);
	}
}

void	get_fd_out(t_token *redirections, t_data *data)
{
	t_token	*current;

	current = redirections;
	while (current)
	{
		if (current->next && current->next->type == T_FILENAME)
		{
			if (current->type == T_REDIR_OUT || current->type == T_REDIR_APPEND)
				open_outfile(current->next->value, data, current->type);
		}
		current = current->next;
	}
}
