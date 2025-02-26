/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:10 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 18:36:33 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	verif_flag(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (false);
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

int	ft_echo(t_cmd *cmd)
{
	bool	n_flag;
	int		i;

	i = 1;
	n_flag = false;
	if (cmd->cmd_args[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (verif_flag(cmd->cmd_args[i]) == true)
	{
		n_flag = true;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		ft_putstr_fd(cmd->cmd_args[i], 1);
		if (cmd->cmd_args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_flag == false)
		ft_putstr_fd("\n", 1);
	return (0);
}
