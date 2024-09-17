/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/17 22:24:50 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void search_in_env(t_data *data, char *var)
{
	t_env	*tmp_env;

	tmp_env = data->env;
	while (tmp_env)
	{
		if (!ft_strcmp(var, tmp_env->line))
		{
			free(tmp_env->line);
			//free(tmp_env);
			//return;
		}
		tmp_env = tmp_env->next;
	}
}

void ft_unset(t_data *data)
{
	t_token	*tmp_tok;
	t_env	*tmp_env;
	bool	after_unset;
	
	tmp_tok = data->tok;
	tmp_env = data->env;
	while (tmp_tok)
	{
		if (after_unset == true)
			search_in_env(data, tmp_tok->value);
		if (!ft_strcmp(tmp_tok->value, "unset"))
			after_unset = true;
		tmp_tok = tmp_tok->next;
	}
}
