/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:05:12 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/05 15:55:28 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_commands(t_data *data)
{
	signal(SIGINT, SIG_IGN);
	while (errno != ECHILD)
	{
		if (wait(&data->wstatus) == data->last_pid)
		{
			if (WIFEXITED(data->wstatus))
				data->exit_status = WEXITSTATUS(data->wstatus);
			else
			{
				data->exit_status = 128 + WTERMSIG(data->wstatus);
				if (data->exit_status == 131)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				else if (data->exit_status == 139)
					ft_putstr_fd("Segmentation fault (core dumped)\n",
						STDERR_FILENO);
			}
			if (data->exit_status == 130)
				ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	if (g_exit_status == 130)
		data->exit_status = 130;
}

void	ft_execution(t_data *data)
{
	signal(SIGQUIT, sigquit_handler);
	read_ast(data->ast, data);
	// print_ast(data->ast, 0);
	// if (data->heredoc)
	// {
	// 	free_ast(&data->ast, data);
	// 	data->heredoc = false;
	// }
	data->exit_status = exec_onecommand(data->ast, data, true);
	free_ast(&data->ast, data);
	wait_commands(data);
}
