/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/25 08:05:03 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_double(t_data *data, char *var)
{
	t_env	*tmp;
	char	*name;
	int		i;

	i = 0;
	if (!data->env)
		return (false);
	tmp = data->env;
	while (var[i] && var[i] != '=')
		i++;
	name = ft_substr(var, 0, i);
	if (!name)
		return (false);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = put_value(var);
			return (free(name), true);
		}
		tmp = tmp->next;
	}
	return (free(name), false);
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
	int	i;

	i = 1;
	if (!argv[i])
		ft_exp_env(data);
	else
	{
		while (argv[i])
		{
			if (check_ifvalue(argv[i]) == false)
			{
				data->exit_status = 0;
				return ;
			}
			if (ft_isdigit(argv[i][0]) || ft_is_operator(argv[i][0])
				|| ft_is_separator(argv[i]) || argv[i][0] == '=')
			{
				ft_putstr_fd("export: not a valid identifier\n", 2);
				data->exit_status = 1;
				return ;
			}
			if (check_double(data, argv[i]) == false)
				push_node_to_env(data, argv[i]);
			i++;
		}
	}
	data->exit_status = 0;
}
