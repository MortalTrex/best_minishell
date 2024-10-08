/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:24:03 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/08 15:24:44 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_to_argv(t_cmd *cmd, char *arg)
{
	int i = 0;

	// Find the current size of argv array
	while (cmd->argv[i] != NULL)
		i++;

	// Reallocate memory for the new argument
	cmd->argv = realloc(cmd->argv, sizeof(char *) * (i + 2));
	if (!cmd->argv)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}

	// Add the new argument and NULL terminate the array
	cmd->argv[i] = arg;
	cmd->argv[i + 1] = NULL;
}

void add_redir_to_cmd(t_cmd *cmd, t_redir *redir)
{
	t_redir *last = cmd->redir;

	// If no redirections exist yet, set the first redirection
	if (!last)
	{
		cmd->redir = redir;
		return;
	}

	// Traverse to the end of the redirection linked list
	while (last->next)
		last = last->next;

	// Add the new redirection to the end of the list
	last->next = redir;
}
