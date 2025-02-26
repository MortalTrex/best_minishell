/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:21 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 14:57:39 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *commands)
{
	char	cwd[4096];

	if (commands->cmd_args[1] && commands->cmd_args[1][0]
			&& commands->cmd_args[1][0] == '-')
	{
		write_error(commands->cmd_args[1], "invalid option", NULL);
		return (2);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("pwd: error retrieving ", STDERR_FILENO);
		perror("current directory: getcwd: cannot access parent directories");
		return (1);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
