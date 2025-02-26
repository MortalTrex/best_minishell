/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 14:57:25 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_exists(t_env *env_head, char *var_name)
{
	t_env	*env;

	env = env_head;
	if (!var_name)
		return (0);
	while (env)
	{
		if (ft_strcmp(env->var_name, var_name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

static void	delete_env_var(t_env *env_head, char *var_name)
{
	t_env	*env;
	t_env	*prev;

	env = env_head;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->var_name, var_name) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				env_head = env->next;
			free(env->var_name);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
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
			return (write_error(cmd[1], "invalid option", "export"), 2);
		if (var_exists(shell->env_list, shell->commands->cmd_args[i]))
			delete_env_var(shell->env_list, shell->commands->cmd_args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
