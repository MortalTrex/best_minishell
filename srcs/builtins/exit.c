/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:15 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/27 16:01:05 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_value(long value, t_data *shell, bool pipe)
{
	if (value > 255 || value < 0)
		value = (value % 256 + 256) % 256;
	if (pipe == false)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	shell->exit_status = value;
}

static int	get_exit_status(t_cmd *commands, char *arg,
				t_data *data, bool pipe)
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
		data->exit_status = 2;
	}
	else if (commands->cmd_args[1] && commands->cmd_args[2])
	{
		if (pipe == false)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		print_error("exit", "too many arguments", NULL);
		data->exit_status = 1;
		return (EXIT_FAILURE);
	}
	else
		ft_value(status, data, pipe);
	return (EXIT_SUCCESS);
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
	ft_free_all_and_exit(data, data->exit_status);
}
