/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:23:05 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 18:19:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_command(t_token *tokens)
{
	t_cmd	*command;

	if (!tokens)
		return (NULL);
	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	ft_memset(command, 0, sizeof(t_cmd));
	command->cmd_args = convert_tokens_to_cmd_array(tokens);
	handle_redirections(tokens, command);
	if (command->cmd_args && command->cmd_args[0])
		command->is_builtin = is_builtin(command->cmd_args[0]);
	return (command);
}

static t_cmd	*get_last_command(t_cmd *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_command_back(t_cmd **commands, t_cmd *new_node)
{
	t_cmd	*temp;

	if (!new_node)
		return ;
	if (*commands && new_node)
	{
		temp = get_last_command(*commands);
		temp->next = new_node;
		new_node->prev = temp;
		new_node->next = NULL;
	}
	else
	{
		*commands = new_node;
		(*commands)->next = NULL;
		(*commands)->prev = NULL;
	}
}
