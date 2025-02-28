/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/28 19:36:36 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_valid_identifier(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	check_if_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	valid_for_export(char *str)
{
	char	**split;

	if (ft_strlen(str) == 0)
		return (print_error("export", "not a valid identifier", str), 1);
	if (!ft_strchr(str, '=') || str[0] == '=')
	{
		if (!check_valid_identifier(str))
			return (print_error("export", "not a valid identifier", str), 1);
		return (-1);
	}
	split = ft_split(str, '=');
	if (ft_strcmp(str, "=") == 0 || !check_valid_identifier(split[0]))
	{
		if (split[0][0] == '-')
			return (print_error("export", "invalid option", split[0]),
				ft_free_tab(split), 2);
		return (print_error("export", "not a valid identifier", str),
			ft_free_tab(split), 1);
	}
	if (!split[1])
		return (ft_free_tab(split), 0);
	if (!check_if_value(split[1]))
		return (ft_free_tab(split), 1);
	return (ft_free_tab(split), 0);
}

static void	handle_export(char *str, t_data *data)
{
	t_env	*tmp;
	char	**split;

	split = ft_split(str, '=');
	tmp = data->env;
	if (!check_if_variable_exists(data->env, split[0]))
		append_env_variable(&data->env, init_env_node(str));
	else
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->name, split[0]) == 0)
			{
				free(tmp->value);
				tmp->value = get_env_value(str, split[0]);
				break ;
			}
			tmp = tmp->next;
		}
	}
	ft_free_tab(split);
}

int	ft_export(char **cmd, t_data *data)
{
	int	i;
	int	exit_code;

	if (!cmd[1])
	{
		ft_env(data);
		return (0);
	}
	i = 1;
	while (cmd[i])
	{
		exit_code = valid_for_export(cmd[i]);
		if (exit_code == 0)
			handle_export(cmd[i], data);
		else if (exit_code == 1)
			return (1);
		else if (exit_code == 2)
			return (2);
		i++;
	}
	return (0);
}
