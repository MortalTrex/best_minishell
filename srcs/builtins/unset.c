/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2025/01/14 12:06:13 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	search_in_env(t_data *data, char *var)
{
	t_env	*current;

	if (!var || !data->env)
		return ;
	current = data->env;
	while (current)
	{
		if (current->name && !ft_strcmp(var, current->name))
		{
			ft_envclear(&data->env);
			return ;
		}
		current = current->next;
	}
}

int	ft_unset(char **argv, t_data *data)
{
	int	i;

	if (!argv || !data)
		return (1);
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			search_in_env(data, argv[i]);
		i++;
	}
	return (0);
}
