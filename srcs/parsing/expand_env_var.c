/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:39:59 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/02 18:04:46 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_value(char *var, t_data *data)
{
	t_env	*current;

	if (ft_strcmp(var, "$UID"))
	{
		return "1";
	}
	if (ft_strcmp(var, "$?"))
	{
		return ft_itoa(data->exit_status);
	}
	current = data->env;
	while (current)
	{
		if (!ft_strcmp(var, current->name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*ft_expand_env_vars(char *word, size_t *i, t_data *data)
{
	char	*env_value;
	char	*var;
	size_t	start;

	(*i)++;
	if (ft_isdigit(word[*i]) || word[*i] == '@')
		return ((*i)++, ft_strdup(""));
	else if (word[*i] == '?')
		return ((*i)++, ft_itoa(data->exit_status));
	else if (!ft_is_wordchar(word[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (ft_is_wordchar(word[*i]))
		(*i)++;
	var = ft_substr(word, start, *i - start);
	env_value = ft_get_env_value(var, data);
	if (!env_value)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_value));
}
