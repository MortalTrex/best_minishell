/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:15 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 18:07:57 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	calculate_exit_status(long status, t_data *shell, bool pipe)
{
	if (status > 255)
		status = status % 256;
	else if (status < 0)
		status = (status % 256) + 256;
	if (pipe == false)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	shell->exit_status = status;
}

static int	get_exit_status(t_cmd *commands, char *arg,
				t_data *shell, bool pipe)
{
	long	status;
	char	*endptr;

	errno = 0;
	status = ft_atoi_long(arg, &endptr);
	if (errno == ERANGE || *endptr != '\0')
	{
		if (pipe == false)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		shell->exit_status = 2;
	}
	else if (commands->cmd_args[1] && commands->cmd_args[2])
	{
		if (pipe == false)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		print_error("exit", "too many arguments", NULL);
		shell->exit_status = 1;
		return (1);
	}
	else
		calculate_exit_status(status, shell, pipe);
	return (0);
}

void	ft_exit(t_cmd *commands, t_data *data, bool pipe)
{
	if (commands->redirs)
		get_fds(commands->redirs, data);
	close_fds(data);
	if (commands->cmd_args[1])
	{
		if (get_exit_status(commands, commands->cmd_args[1], data, pipe) == 1)
			return ;
	}
	else if (pipe == false)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_and_exit(data, data->exit_status);
}
