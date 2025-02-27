/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:28:14 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/27 15:21:53 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_default_env(void)
{
	t_env	*new;
	t_env	*res;

	res = NULL;
	new = init_default_env_node("PWD", getcwd(NULL, 0));
	if (!new)
		return (ft_free_env(res), NULL);
	append_env_variable(&res, new);
	new = init_default_env_node("SHLVL", "1");
	if (!new)
		return (ft_free_env(res), NULL);
	append_env_variable(&res, new);
	new = init_default_env_node("_", "/usr/bin/env");
	if (!new)
		return (ft_free_env(res), NULL);
	append_env_variable(&res, new);
	append_env_variable(&res, NULL);
	return (res);
}

t_env	*init_env(char **env)
{
	int		i;
	t_env	*head;
	t_env	*new_node;

	i = 0;
	head = NULL;
	while (env[i])
	{
		new_node = init_env_node(env[i]);
		if (!new_node)
			return (ft_free_env(head), NULL);
		append_env_variable(&head, new_node);
		i++;
	}
	append_env_variable(&head, NULL);
	if (!head)
		head = init_default_env();
	return (head);
}

static int	list_len(t_env *env_head)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env_head;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

static char	**fill_env_array(t_env *current, char **res)
{
	int		i;
	char	*tmp;

	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->name, "=");
		if (!tmp)
			return (ft_free_tab(res), NULL);
		if (current->value)
		{
			res[i] = ft_strjoin(tmp, current->value);
			free(tmp);
			if (!res[i])
				return (ft_free_tab(res), NULL);
		}
		i++;
		current = current->next;
	}
	res[i] = NULL;
	return (res);
}

char	**init_env_array(t_env *env_head)
{
	t_env	*current;
	char	**res;

	current = env_head;
	res = malloc(sizeof(char *) * (list_len(current) + 1));
	if (!res)
		return (NULL);
	return (fill_env_array(current, res));
}
