/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:15 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/04 19:18:17 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
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
	printf("LA VALEUR : %d\n", value);
	if (value > 255 || value < 0)
		value = (value % 256 + 256) % 256;
	printf("LA VALEUR APRES : %d\n", value);
	return (value);
}

void	ft_exit(char **argv, t_data *data)
{
	int		value;

	if (argv[1])
	{
		if (ft_is_number(argv[1]))
		{
			value = ft_atoi(argv[1]);
			value = ft_value(value);
			ft_free_all(data);
			exit(value);
		}
		else
			ft_error(data, "exit: numeric argument required\n");
	}
	else
	{
		ft_free_all(data);
		exit(0);
	}
}
