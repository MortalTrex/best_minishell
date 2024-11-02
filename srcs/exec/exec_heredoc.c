/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 00:04:45 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/03 00:14:07 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_process_heredoc(t_redir *redir, t_data *data)
{
	int			fd[2];
	pid_t		pid;

	pipe(fd);
	data->child_status = true;
	pid = (signal(SIGQUIT, SIG_IGN), fork());
	if (!pid)
	{
		signal(SIGINT, );
	}
}
