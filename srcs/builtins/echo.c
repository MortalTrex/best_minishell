/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:10 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 14:57:39 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_for_n_flag(t_cmd *commands, bool *n_flag, int *i)
{
	int	j;

	while (commands->cmd_args[*i] && commands->cmd_args[*i][0] == '-')
	{
		j = 1;
		while (commands->cmd_args[*i][j] == 'n')
			j++;
		if (commands->cmd_args[*i][j] == '\0')
			*n_flag = true;
		else
			break ;
		(*i)++;
	}
}

static void	write_commands(t_cmd *commands, bool n_flag, int *i)
{
	while (commands->cmd_args[*i])
	{
		write(STDOUT_FILENO, commands->cmd_args[*i],
			ft_strlen(commands->cmd_args[*i]));
		if (commands->cmd_args[*i + 1] && commands->cmd_args[*i + 1][0] != '\0')
			write(STDOUT_FILENO, " ", 1);
		(*i)++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
}

int	ft_echo(t_cmd *commands)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 1;
	if (!commands->cmd_args[i])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (commands->cmd_args[i][0] == '-' && commands->cmd_args[i][1] == 'n')
		check_for_n_flag(commands, &n_flag, &i);
	write_commands(commands, n_flag, &i);
	return (0);
}
