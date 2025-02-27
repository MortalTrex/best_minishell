/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:22:04 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/27 15:49:49 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all_and_exit(t_data *shell, int exit_code)
{
	if (shell)
	{
		free_data(shell);
		if (shell->env)
			ft_free_env((shell->env));
	}
	rl_clear_history();
	exit(exit_code);
}

void	free_data(t_data *shell)
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

void	free_commands(t_cmd **commands)
{
	t_cmd	*temp;
	t_cmd	*current;

	if (!*commands)
		return ;
	current = *commands;
	while (current)
	{
		temp = current->next;
		if (current->cmd_args)
			ft_free_tab(current->cmd_args);
		free_tokens(&(current->redirs));
		free(current);
		current = temp;
	}
	*commands = NULL;
}
