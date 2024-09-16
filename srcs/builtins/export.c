/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/16 17:18:36 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_export(t_data *data)
{
	t_token *current;
	bool	after_export;
	char	*value;

	current = data->tok;
	after_export = false;
	value = NULL;
	while (current)
	{
		if (after_export == true)
			value = ft_strjoin(value, current->value);
		if (!ft_strcmp(current->value, "export"))
		{
			after_export = true;
			push_node_to_env(data, value);
		}
		current = current->next;
	}
	printf("export vaut : %s\n", value);
	free(value);
}
