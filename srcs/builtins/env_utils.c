/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:31:17 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 18:35:50 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*allocate_env_value_memory(char *str, size_t var_name_len)
{
	char	*value;
	size_t	full_str_len;

	full_str_len = ft_strlen(str);
	if (var_name_len + 1 == full_str_len)
	{
		value = malloc(2);
		if (!value)
			return (NULL);
		value[0] = ' ';
		value[1] = '\0';
	}
	else if (var_name_len == full_str_len)
		value = NULL;
	else
	{
		value = malloc(full_str_len - var_name_len);
		if (!value)
			return (NULL);
	}
	return (value);
}

char	*get_env_value(char *str, char *var_name)
{
	size_t	var_name_len;
	char	*value;

	var_name_len = ft_strlen(var_name);
	value = allocate_env_value_memory(str, var_name_len);
	if (value != NULL)
		ft_strlcpy(value, str + var_name_len + 1, ft_strlen(str)
			- var_name_len);
	return (value);
}

t_env	*init_env_node(char *str)
{
	char	**split;
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	split = ft_split(str, '=');
	if (!split)
		return (NULL);
	env_node->name = ft_strdup(split[0]);
	if (!env_node->name)
		return (NULL);
	env_node->value = get_env_value(str, split[0]);
	env_node->next = NULL;
	ft_free_tab(split);
	return (env_node);
}

t_env	*init_default_env_node(char *var_name, char *value)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->name = ft_strdup(var_name);
	env_node->value = ft_strdup(value);
	env_node->next = NULL;
	return (env_node);
}

void	append_env_variable(t_env **head, t_env *new_node)
{
	t_env	*current;

	if (!new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
