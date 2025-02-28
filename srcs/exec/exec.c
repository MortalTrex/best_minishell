/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:33 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/28 19:40:12 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_detect_builtin(t_cmd *commands, t_data *data, bool pipe)
{
	if (!ft_strcmp(commands->cmd_args[0], "cd"))
		data->exit_status = ft_cd(commands, data);
	else if (!ft_strcmp(commands->cmd_args[0], "pwd"))
		data->exit_status = ft_pwd(commands);
	else if (!ft_strcmp(commands->cmd_args[0], "echo"))
		data->exit_status = ft_echo(commands);
	else if (!ft_strcmp(commands->cmd_args[0], "export"))
		data->exit_status = ft_export(commands->cmd_args, data);
	else if (!ft_strcmp(commands->cmd_args[0], "unset"))
		data->exit_status = ft_unset(commands->cmd_args, data);
	else if (!ft_strcmp(commands->cmd_args[0], "env"))
		data->exit_status = ft_env(data);
	else if (!ft_strcmp(commands->cmd_args[0], "exit"))
		ft_exit(commands, data, pipe);
	if (pipe == true)
		ft_free_all_and_exit(data, data->exit_status);
}

static void	execute_command(t_cmd *current, t_data *data)
{
	char	**env;

	env = NULL;
	signal(SIGQUIT, SIG_DFL);
	if (!current->cmd_args[0])
	{
		data->exit_status = 0;
		ft_free_all_and_exit(data, data->exit_status);
	}
	
	if (current->is_builtin == true)
		ft_detect_builtin(current, data, true);
	else
	{
		data->cmd_path = get_cmd_path(current->cmd_args[0], data);
		if (!data->cmd_path)
			handle_error(current->cmd_args[0], "command not found", 127, data);
		env = init_env_array(data->env);
		execve(data->cmd_path, current->cmd_args, env);
		ft_free_tab(env);
		perror(data->cmd_path);
		if (data && data->cmd_path)
			free(data->cmd_path);
		ft_free_all_and_exit(data, data->exit_status);
	}
}

static int	handle_parent(t_cmd *current, t_data *data, int prev_fd)
{
	if (prev_fd != 0)
		close(prev_fd);
	if (current->next)
	{
		close(data->pipe_fd[1]);
		prev_fd = data->pipe_fd[0];
	}
	close_fds(data);
	return (prev_fd);
}

static void	handle_child(t_cmd *current, t_data *data, int prev_fd)
{
	if (current->redirs)
		open_and_redirect_fd(current, data);
	has_no_filename(current, data, prev_fd);
	execute_command(current, data);
}

int	executing(t_data *data)
{
	t_cmd		*current;
	int			prev_fd;

	if (data == NULL || data->commands == NULL)
		return (-1);
	current = data->commands;
	prev_fd = 0;
	if (!current->next && current->is_builtin == true && (!current->redirs
			|| ft_strcmp(current->cmd_args[0], "exit") == 0))
		ft_detect_builtin(current, data, false);
	else
	{
		while (current)
		{
			pipe_and_fork(current, data);
			if (data->prev_pid == 0)
				handle_child(current, data, prev_fd);
			else
				prev_fd = handle_parent(current, data, prev_fd);
			current = current->next;
		}
	}
	wait_commands(data);
	return (data->exit_status);
}
