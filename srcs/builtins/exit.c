/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:15 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/10 17:13:15 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_value(int value)
{
	if (value > 255)
		value = value % 256;
	return (value);
}

void	ft_exit(t_data *data)
{
	t_token	*current;
	int		value;

	current = data->tok;
	if (current->next)
	{
		current = current->next;
		if (current->type == T_WORD)
		{
			if (ft_is_number(current->value))
			{
				value = ft_atoi(current->value);
				value = ft_value(value);
				ft_free_all(data);
				//printf("current->value: %d\n", value);
				exit(value);
			}
			else
				ft_error(data, "exit: numeric argument required\n");
		}
		else
			ft_error(data, "exit: numeric argument required\n");
	}
	ft_free_all(data);
	exit(0);
}
