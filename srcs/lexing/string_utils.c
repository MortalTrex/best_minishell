/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:44:45 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 16:12:27 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_env_value(char *str, t_env *env_list, char *name, \
	char *d_quoted)
{
	t_env	*temp;

	name++;
	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	if (d_quoted || ft_strcmp(str, name) != 0)
		return ("");
	return (NULL);
}

static char	*parse_env_from_string(char *str)
{
	int		i;
	char	*var_name;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (free(str), NULL);
	ft_strlcpy(var_name, str, i + 1);
	return (var_name);
}

static char	*replace_substring(char *str, char *old_value, char *new_value, \
	int last_index)
{
	char	*new_str;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(new_value) - ft_strlen(old_value) + ft_strlen(str);
	new_str = malloc(size + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j <= size)
	{
		if (!ft_strncmp(str + i, old_value, ft_strlen(old_value)) && \
				i == last_index)
		{
			j += ft_strlcpy(new_str + j, new_value, ft_strlen(new_value) + 1);
			ft_strlcpy(new_str + j, str + i + ft_strlen(old_value), \
					ft_strlen(str) - i);
			return (new_str);
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*get_value_after_expansion(char *str, t_data *data, int *i)
{
	char	*d_quoted;
	char	*env_var;
	char	*val;
	char	*updated_string;

	d_quoted = ft_strchr(str, DQ);
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		val = ft_itoa(data->exit_status);
		updated_string = replace_substring(str, "$?", val, *i);
		return (free(val), free(str), updated_string);
	}
	env_var = parse_env_from_string(str + *i);
	if (!env_var)
		return (free(str), NULL);
	val = extract_env_value(str, data->env, env_var, d_quoted);
	if (!val && *i == 0 && ft_strcmp(str, env_var) != 0)
	{
		updated_string = ft_strtrim(str, env_var);
		return (free(env_var), free(str), updated_string);
	}
	updated_string = replace_substring(str, env_var, val, *i);
	*i = 0;
	return (free(env_var), free(str), updated_string);
}
