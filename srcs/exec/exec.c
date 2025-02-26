/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:33 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 15:13:33 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exec_builtin(t_cmd *commands, t_data *shell, bool pipe)
{
	if (ft_strcmp(commands->cmd_args[0], "cd") == 0)
		shell->exit_status = ft_cd(commands, shell);
	else if (ft_strcmp(commands->cmd_args[0], "pwd") == 0)
		shell->exit_status = ft_pwd(commands);
	else if (ft_strcmp(commands->cmd_args[0], "echo") == 0)
		shell->exit_status = ft_echo(commands);
	else if (ft_strcmp(commands->cmd_args[0], "export") == 0)
		shell->exit_status = ft_export(commands->cmd_args, shell);
	else if (ft_strcmp(commands->cmd_args[0], "unset") == 0)
		shell->exit_status = ft_unset(commands->cmd_args, shell);
	else if (ft_strcmp(commands->cmd_args[0], "env") == 0)
		shell->exit_status = ft_env(shell);
	else if (ft_strcmp(commands->cmd_args[0], "exit") == 0)
		ft_exit(commands, shell, pipe);
	if (pipe == true)
		free_and_exit(shell, shell->exit_status);
}

static void	execute_command(t_cmd *current, t_data *shell)
{
	char	**env;

	env = NULL;
	signal(SIGQUIT, SIG_DFL);
	if (!current->cmd_args[0])
	{
		shell->exit_status = 0;
		free_and_exit(shell, shell->exit_status);
	}
	if (current->is_builtin == true)
		exec_builtin(current, shell, true);
	else
	{
		shell->cmd_path = get_cmd_path(current->cmd_args[0], shell);
		if (!shell->cmd_path)
			handle_error(current->cmd_args[0], "command not found", 127, shell);
		env = init_env_array(shell->env_list);
		execve(shell->cmd_path, current->cmd_args, env);
		free_array(env);
		perror(shell->cmd_path);
		if (shell && shell->cmd_path)
			free(shell->cmd_path);
		free_and_exit(shell, shell->exit_status);
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

static void	handle_child(t_cmd *current, t_data *shell, int prev_fd)
{
	if (current->redirs)
		open_and_redirect_fd(current, shell);
	has_no_filename(current, shell, prev_fd);
	execute_command(current, shell);
}

int	executing(t_data *data)
{
	t_cmd	*current;
	int			prev_fd;

	if (data == NULL || data->commands == NULL)
		return (-1);
	current = data->commands;
	prev_fd = 0;
	if (!current->next && current->is_builtin == true && (!current->redirs
			|| ft_strcmp(current->cmd_args[0], "exit") == 0))
		exec_builtin(current, data, false);
	else
	{
		while (current)
		{
			pipe_and_fork(current, data);
			if (data->last_pid == 0)
				handle_child(current, data, prev_fd);
			else
				prev_fd = handle_parent(current, data, prev_fd);
			current = current->next;
		}
	}
	wait_commands(data);
	return (data->exit_status);
}
