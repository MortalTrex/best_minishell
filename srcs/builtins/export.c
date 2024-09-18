/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/18 15:58:26 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_swap_env_lines(t_env *a, t_env *b)
{
	char	*temp;

	temp = a->line;
	a->line = b->line;
	b->line = temp;
}

void	ft_sort_env(t_env *env)
{
	t_env	*tmp;
	bool	is_sort;

	is_sort = false;
	while (is_sort == false)
	{
		is_sort = true;
		tmp = env;
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->line, tmp->next->line) > 0)
			{
				ft_swap_env_lines(tmp, tmp->next);
				is_sort = false;
			}
			tmp = tmp->next;
		}
	}
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
		ft_printf("declare -x %s\n", tmp->line);
		tmp = tmp->next;
	}
}

void	ft_export(t_data *data)
{
	t_token	*tmp;
	bool	exiafter_export;
	int		i;

	tmp = data->tok;
	after_export = false;
	i = 0;
	while (tmp)
	{
		if (after_export == true)
			push_node_to_env(data, tmp->value);
		if (!ft_strcmp(tmp->value, "export"))
			after_export = true;
		tmp = tmp->next;
		i++;
	}
	if (i == 1 && after_export == true)
		ft_exp_env(data);
}
