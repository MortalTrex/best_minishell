/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:22:04 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/25 15:51:23 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit_shell(t_shell *shell, int exit_code)
{
	if (shell)
	{
		free_shell(shell);
		if (shell->env_list)
			free_env((shell->env_list));
	}
	rl_clear_history();
	exit(exit_code);
}

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->heredoc)
		{
			free(shell->heredoc);
			shell->heredoc = NULL;
		}
		if (shell->tokens)
			free_tokens(&(shell->tokens));
		if (shell->commands)
			free_commands(&(shell->commands));
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*temp;
	t_token	*current;

	if (!*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		temp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
	*tokens = NULL;
}

void	free_commands(t_command **commands)
{
	t_command	*temp;
	t_command	*current;

	if (!*commands)
		return ;
	current = *commands;
	while (current)
	{
		temp = current->next;
		if (current->cmd_name)
			free_array(current->cmd_name);
		free_tokens(&(current->redirections));
		free(current);
		current = temp;
	}
	*commands = NULL;
}