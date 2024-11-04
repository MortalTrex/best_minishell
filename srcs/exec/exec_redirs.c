/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:44:32 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/04 17:13:34 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_append(t_redir *redir)
{
	int	fd;

	if (!redir->argv || redir->argv[1])
		return (1);
	fd = open(redir->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_process_infile(t_redir *redir)
{
	int	fd;

	if (!redir->argv || redir->argv[1])
		return (1);
	fd = open(redir->argv[0], O_RDONLY);
	if (fd == -1)
		return (perror("open"), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_process_outfile(t_redir *redir)
{
	int	fd;

	if (!redir->argv || redir->argv[1])
		return (1);
	fd = open(redir->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_process_redirections(t_ast_node *node)
{
	t_redir	*redirs;
	int		status;

	redirs = node->redir;
	while(redirs)
	{
		if (redirs->type == T_REDIR_IN)
			return (ft_process_infile(redirs));
		else if (redirs->type == T_REDIR_OUT)
			return (ft_process_outfile(redirs));
		else if (redirs->type == T_REDIR_APPEND)
			return(ft_process_append(redirs));
		else if(redirs->type == T_REDIR_HERE)
			(dup2(redirs->hd_fd, 0), close(redirs->hd_fd));
		redirs = redirs->next;
	}
	return (1); // handle error statuses
}
