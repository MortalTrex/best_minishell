/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:10 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/31 18:10:17 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	verif_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	ft_echo(char **argv)
{
	bool	n_flag;
	int 	i;

	i = 1;
	n_flag = false;
	if (verif_flag(argv[i]) == true)
	{
		n_flag = true;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (n_flag == false)
		ft_printf("\n");
}

