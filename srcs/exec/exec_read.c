/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:42:47 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/03 00:04:13 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_command(t_ast_node *node, t_data *data)
{
	t_redir	*redirs;
	pid_t	pid;

	redirs = node->redir;
	while (redirs)
	{
		if (redirs->type == D_HEREDOC)
			ft_process_heredoc(redirs->command, data);
		if (redirs->type == IN)
			ft_process_infile(redirs->command, data, false);
		if (redirs->type == OUT)
			ft_process_outfile(redirs->command, data);
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
			if (!data->child)
				read_ast(node->right);
	}
	else
		read_command(node, data);

}

void	ft_execution(t_data *data)
{
	while (current)
	{
		if (current->type == T_WORD && i == 0)
		{
			if (exec_onecommand(current->value, data) == -1)
				ft_error(data, "Error: exec failed\n");
			cmd = ft_strdup(current->value);
		}
		if (current-> type == T_PIPE)
		{
			printf("current->value: %s\n", current->value);
			exec_pipe(cmd, current->next->value, data);
			free(cmd);
		}
		if (current)
			current = current->next;
		i++;
	}
}
