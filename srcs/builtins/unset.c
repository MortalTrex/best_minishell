/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/27 15:16:16 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_variable_exists(t_env *env, char *var)
{
	t_env	*current;

	current = env;
	if (!var)
		return (0);
	while (current)
	{
		if (!ft_strcmp(current->name, var))
			return (1);
		current = current->next;
	}
	return (0);
}

static void	search_in_env(t_env *env_head, char *var)
{
	t_env	*current;
	t_env	*prev;

	current = env_head;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->name, var))
		{
			if (prev)
				prev->next = current->next;
			else
				env_head = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(char **cmd, t_data *shell)
{
	int	i;

	if (!cmd[1])
		return (EXIT_SUCCESS);
	i = 1;
	while (cmd[i])
	{
		if (cmd[1][0] == '-')
			return (print_error(cmd[1], "invalid option", "export"), 2);
		if (check_if_variable_exists(shell->env, shell->commands->cmd_args[i]))
			search_in_env(shell->env, shell->commands->cmd_args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
