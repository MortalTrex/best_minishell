/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:24:03 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/14 20:09:52 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_to_argv(t_cmd *cmd, char *arg, t_data *data)
{
	int i = 0;

	while (cmd->argv[i] != NULL)
		i++;
	cmd->argv = realloc(cmd->argv, sizeof(char *) * (i + 2));
	if (!cmd->argv)
		ft_error(data, "Error: realloc failed to allocate memory\n");
	cmd->argv[i] = ft_strdup(arg);
	cmd->argv[i + 1] = NULL;
}

void add_redir_to_cmd(t_cmd *cmd, t_redir *redir)
{
	t_redir *last;
	
	last = cmd->redir;
	if (!last)
	{
		cmd->redir = redir;
		return;
	}
	while (last->next)
		last = last->next;
	last->next = redir;
}
