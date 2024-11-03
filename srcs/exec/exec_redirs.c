/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:44:32 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/03 21:14:21 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_infile(char **argv, t_data *data)
{
	int	fd_in;

	if (!argv || !argv[1])
		ft_close_fd(data, "Error: no cmd\n");
	{
		fd_in = open(argv[0], O_RDONLY);
		if (fd_in == -1)
			ft_close_fd(data, "Error opening fd_in");
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			ft_close_fd(data, "Error redirecting stdout");
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_close_fd(data, "Error redirecting stdin");
		close(data->fd[0]);
		close(data->fd[1]);
		close(fd_in);
	}
	exec(data, cmd);
	exit(EXIT_SUCCESS);
}

void	ft_process_outfile(char *cmd, t_data *data)
{
	int	fd_out;

	fd_out = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		ft_close_fd(data, "Error opening fd_out\n");
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		ft_close_fd(data, "Error redirecting stdin\n");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_close_fd(data, "Error redirecting stdout\n");
	close(data->fd[0]);
	close(data->fd[1]);
	close(fd_out);
	exec(data, cmd);
}

int	ft_process_redirections(t_ast_node *node)
{
	t_redir	*redirs;
	int		status;

	redirs = node->redir;
	while(redirs)
	{
		if (redirs->type == T_REDIR_IN)
			return(ft_process_infile(redirs));
		else if (redirs->type == T_REDIR_OUT)
			return(ft_process_outfile(redirs));
		else if (redirs->type == T_REDIR_APPEND)
			return(ft_process_append(redirs));
		else if(redirs->type == T_REDIR_HERE)
			(dup2(redirs->hd_fd, 0), close(redirs->hd_fd));
		redirs = redirs->next;
	}
	return (1); // handle error statuses
}
