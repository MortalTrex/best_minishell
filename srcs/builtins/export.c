/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/10 14:07:58 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_double(t_data *data, char *name, char *value)
{
	t_env	*tmp;

	if (!data->env)
		return (false);
	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

void	ft_exp_env(t_data *data)
{
	t_env	*tmp;

	if (!data || !data->env)
		return ;
	ft_sort_env(data->env);
	tmp = data->env;
	while (tmp != NULL)
	{
		if (tmp->line)
			ft_printf("declare -x %s\n", tmp->line);
		tmp = tmp->next;
	}
}

bool	check_ifvalue(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

void	ft_export(char **argv, t_data *data)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_sign;

	i = 1;
	equal_sign = NULL;
	if (!argv[i])
		ft_exp_env(data);
	else
	{
		while (argv[i])
		{
			if (i == 1 && !ft_strcmp(argv[i], "-p"))
			{
				ft_exp_env(data);
				i++;
				continue ;
			}
			name = ft_substr(argv[i], 0, equal_sign - argv[i]);
			value = ft_strdup(equal_sign + 1);
			if (ft_isdigit(name[0]) || ft_is_operator(name[0])
				|| ft_is_separator(name) || name[0] == '=')
			{
				ft_putstr_fd("export: not a valid identifier\n", 2);
				data->exit_status = 1;
				free(name);
				free(value);
				return ;
			}
			if (check_double(data, name, value) == false)
			{
				char *name_value = ft_strjoin(name, "=");
				char *full_name_value = ft_strjoin(name_value, value);
				free(name_value);
				push_node_to_env(data, full_name_value);
				free(full_name_value);
			}
			else
			{
				char *name_value = ft_strjoin(name, "=");
				char *full_name_value = ft_strjoin(name_value, value);
				free(name_value);
				push_node_to_env(data, full_name_value);
				free(full_name_value);
			}
			free(name);
			free(value);
			i++;
		}
	}
	data->exit_status = 0;
}
