/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2025/01/14 15:47:08 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_double(t_data *data, char *var)
{
	t_env	*tmp;
	char	*name;
	int		i;

	i = 0;
	tmp = data->env;
	if (!tmp)
		return (false);
	while (var[i] && var[i] != '=')
		i++;
	name = ft_substr(var, 0, i);
	if (!name)
		return (false);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			ft_free((void **)&tmp->value);
			tmp->value = put_value(var);
			return (ft_free((void **)&name), true);
		}
		tmp = tmp->next;
	}
	return (ft_free((void **)&name), false);
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
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->line, 1);
			ft_putstr_fd("\n", 1);
		}
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

bool	check_valid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) || ft_is_operator(str[i]) || ft_is_separator_export(str) || !ft_isalpha(str[i]))
			return (false);
		if (str[i] == '-')
			return (false);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i == 0)
				return (false);
			if (ft_is_operator(str[i - 1]))
				return (false);
			return (true);
		}
		i++;
	}
	return (true);
}

int	ft_export(char **argv, t_data *data)
{
	int	i;

	i = 1;
	if (!argv[i])
		ft_exp_env(data);
	else
	{
		while (argv[i])
		{
			if (check_valid_identifier(argv[i]) == false)
			{
				ft_putstr_fd("export: not a valid identifier\n", 2);
				return (1);
			}
			if (check_ifvalue(argv[i]) == true && check_double(data,
					argv[i]) == false)
				push_node_to_env(data, argv[i]);
			i++;
		}
	}
	return (0);
}
