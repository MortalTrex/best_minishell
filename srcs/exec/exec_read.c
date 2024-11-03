/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:42:47 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/03 17:20:49 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_command(t_ast_node *node, t_data *data)
{
	t_redir	*redirs;

	redirs = node->redir;
	while (redirs)
	{
		if (redirs->type == D_HEREDOC)
			ft_process_heredoc(redirs->command, data);
		else
			redirs->argv = ft_expand_and_clean(redirs->command, data);
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
			if (!data->heredoc_signal)
				read_ast(node->right, data);
	}
	else
		read_command(node, data);

}

void	ft_execution(t_data *data)
{
	signal(SIGQUIT, sigquit_handler);
	read_ast(data->ast, data);
	if (data->heredoc_signal)
	{
		free_ast(&data->ast, data);
		data->heredoc_signal = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &data->terminal);
	data->exit_status = ft_excute_ast(data->ast, data);
	free_ast(&data->ast, data);
}
