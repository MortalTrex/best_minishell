/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:46:03 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/03/01 16:34:29 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	push_node_to_env(t_data *data, char *env_line)
{
	t_env	*new_node;
	t_env	*current;

	new_node = init_env_node(env_line);
	if (!new_node)
		return ;
	current = data->env;
	if (data->env == NULL)
		data->env = new_node;
	else
	{
		current = data->env;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
} */

/* void	change_shlvl(t_data *data)
{
	t_env   *tmp;
	char    *shlvl;
	int lvl_int;

	if (!data || !data->env)
	{
		fprintf(stderr, "Error: data or data->env is NULL\n");
		return ;
	}
	lvl_int = 0;
	tmp = data->env;
	while (tmp)
	{
		if (tmp->line && ft_strncmp(tmp->line, "SHLVL=", 6) == 0)
		{
			shlvl = ft_substr(tmp->line, 6, ft_strlen(tmp->line) - 6);
			if (!shlvl)
			{
				fprintf(stderr, "Error: ft_substr returned NULL\n");
				return ;
			}
			lvl_int = ft_atoi(shlvl);
			free(shlvl);
			break ;
		}
		tmp = tmp->next;
	}
	if (lvl_int == 0)
	{
		tmp->line = ft_strdup("SHLVL=1");
		ft_export(&tmp->line, data);
		return ;
	}
	lvl_int++;
	shlvl = ft_itoa(lvl_int);
	if (!shlvl)
	{
		fprintf(stderr, "Error: ft_itoa returned NULL\n");
		return ;
	}
	tmp = data->env;
	while (tmp)
	{
		if (tmp->line && ft_strncmp(tmp->line, "SHLVL=", 6) == 0)
		{
			if (tmp->value)
			{
				free(tmp->value);
			}
			tmp->value = ft_strdup(shlvl);
			if (!tmp->value)
			{
				fprintf(stderr, "Error: ft_strdup returned NULL\n");
				free(shlvl);
				return ;
			}
			if (tmp->line)
			{
				free(tmp->line);
			}
			tmp->line = ft_strjoin("SHLVL=", shlvl);
			if (!tmp->line)
			{
				fprintf(stderr, "Error: ft_strjoin returned NULL\n");
				free(shlvl);
				return ;
			}
			free(shlvl);
			break ;
		}
		tmp = tmp->next;
	}
} */
