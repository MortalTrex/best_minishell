/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:10 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/02 11:32:11 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_data *data)
{
	t_token	*current;
	bool	n_flag;

	current = data->tok;
	current = current->next;
	n_flag = false;
	if (!ft_strcmp(current->value, "-n"))
	{
		n_flag = true;
		current = current->next;
	}
	while (current)
	{
		ft_printf("%s", current->value);
		if (current->next)
			ft_printf(" ");
		current = current->next;
	}
	if (n_flag == false)
		ft_printf("\n");
}
