/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:15 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 14:52:40 by mmiilpal         ###   ########.fr       */
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

static int	get_exit_status(t_command *commands, char *arg,
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
	else if (commands->cmd_name[1] && commands->cmd_name[2])
	{
		if (pipe == false)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		write_error("exit", "too many arguments", NULL);
		shell->exit_status = 1;
		return (1);
	}
	else
		calculate_exit_status(status, shell, pipe);
	return (0);
}

void	ft_exit(t_command *commands, t_data *shell, bool pipe)
{
	if (commands->redirections)
		get_fds(commands->redirections, shell);
	close_fds(shell);
	if (commands->cmd_name[1])
	{
		if (get_exit_status(commands, commands->cmd_name[1], shell, pipe) == 1)
			return ;
	}
	else if (pipe == false)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_and_exit_shell(shell, shell->exit_status);
}
