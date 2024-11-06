/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:42:47 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/06 15:32:02 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_command(t_ast_node *node, t_data *data)
{
	t_redir	*redirs;
	int		fd[2];
	pid_t	pid;

	redirs = node->redir;
	while (redirs)
	{
		if (redirs->type == D_HEREDOC)
		{
			pipe(fd);
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				ft_process_heredoc(redirs, data);
			if

		}
		else
			redirs->argv = ft_expand_and_clean(redirs->file, data);
		redirs = redirs->next;
	}
}

void	read_ast(t_ast_node *node, t_data *data)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		read_ast(node->left, data);
			if (!data->heredoc)
				read_ast(node->right, data);
	}
	else
		read_command(node, data);
}

