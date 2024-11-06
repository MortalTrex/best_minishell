/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/31 18:10:26 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_in_env(t_data *data, char *var)
{
	t_env	*tmp_env;

	tmp_env = data->env;
	while (tmp_env)
	{
		if (!ft_strcmp(var, tmp_env->line))
		{
			free(tmp_env->line);
			tmp_env->line = NULL;
			return ;
		}
		tmp_env = tmp_env->next;
	}
}

void	ft_unset(char **argv, t_data *data)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (ft_isdigit(argv[i][0]) || ft_is_operator(argv[i][0]))
		{
			ft_printf("unset: not a valid identifier\n");
			return ;
		}
		search_in_env(data, argv[i]);
		i++;
	}
}
