/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/19 18:22:08 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_double(t_data *data, char *var)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->line, var))
			return (true);
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

void	change_value(t_data *data, char *old, char *new)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->line, old))
		{
			tmp->line = ft_strdup(new);
			break ;
		}
		tmp = tmp->next;
	}
}

bool	check_change_value(t_data *data)
{
	t_token	*tmp;
	char	*old_str;
	char	*new_str;

	old_str = NULL;
	new_str = NULL;
	tmp = data->tok;
	while (tmp)
	{
		if (!ft_strcmp(tmp->value, "="))
		{
			tmp = tmp->next;
			new_str = ft_strdup(tmp->value);
			change_value(data, old_str, new_str);
			return (free(old_str), free(new_str), true);
		}
		if (tmp->value)
			old_str = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return (free(old_str), free(new_str), false);
}

bool check_ifvalue(char *str)
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
	int i;

	i = 1;
	if (!argv[i])
	{
		ft_exp_env(data);
		return ;
	}
	while (argv[i])
	{
		if (check_ifvalue(argv[i]) == false)
		{
			data->exit_status = 0;
			return ;
		}
		if (ft_isdigit(argv[i][0]) || ft_is_operator(argv[i][0]) || ft_is_separator(argv[i])
			|| argv[i][0] == '=')
		{
			ft_printf("export: not a valid identifier\n");
			data->exit_status = 1;
			return ;
		}
		if (check_double(data, argv[i]) == true)
			// change_value(data, argv[i], argv[i]);
			printf("change value\n");
		else
			push_node_to_env(data, argv[i]);
		i++;
	}
	data->exit_status = 0;
}
