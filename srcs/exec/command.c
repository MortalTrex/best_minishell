/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:52:35 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/05 16:08:18 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	ft_exec_builtin(char *cmd, t_data *data)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(data), 0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(data), 0);
	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(data), 0);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(), 0);
	if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(data), 0);
	if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(data), 0);
	ft_exit(data);
	return (1);
}

static int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static int	exec(t_ast_node *node, t_data *data)
{
	char	*path;
	int		status;
	pid_t	pid;

	pid = fork();
	if(!pid)
	{
		status = ft_process_redirs(node);
		// if (status != 0)
		// {
		// 	ft_free_all(data);
		// 	exit(status);
		// }
		path = ft_path(node->argv[0], data);
		if (!path)
		{
			ft_printf("Command '%s'", node->argv[0]);
			ft_close_fd(data, " not found\n");
		}
		if (execve(path, node->argv, data->envc) == -1)
		{
			ft_free_all(data);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &status, 0);
	return(get_exit_status(status));
}

int	exec_onecommand(t_ast_node *node, t_data *data, bool ispipe)
{
	int		status;

	ispipe = true;
	if (!(node->argv))
		return (EXIT_SUCCESS);
	else if (is_builtin(node->argv[0]))
	{
		status = ft_exec_builtin(node->argv[0], data);
		return (status);
	}
	else
		return (exec(node, data));
}
