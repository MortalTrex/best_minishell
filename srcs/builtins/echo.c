/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:10 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/30 19:24:44 by rbalazs          ###   ########.fr       */
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

void	ft_echo(t_data *data)
{
	t_token	*current;
	bool	n_flag;

	printf("echo\n");
	current = data->tok;
	current = current->next;
	n_flag = false;
	if (verif_flag(current->value) == true)
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
