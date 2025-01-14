/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:56:36 by rbalazs           #+#    #+#             */
/*   Updated: 2025/01/14 15:46:43 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_export_envp(char *str);

int	lstadd_envp(t_data *data, char *str)
{
	t_env	*new;
	t_env	*tmp;

	new = new_export_envp(str);
	if (!new)
		return (ERROR);
	tmp = data->env;
	if (!tmp)
	{
		tmp = new;
	}
	else
	{
		while (tmp)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (SUCCESS);
}

static t_env	*new_export_envp(char *str)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	new->line = ft_strdup(str);
	if (!new->line)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

bool	ft_is_separator_export(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t' || *s == '<'
		|| *s == '>' || *s == '|' || *s == '(' || *s == ')')
		return (true);
	return (false);
}
