/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:33 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/10 17:07:34 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_path(char *cmd, t_data *data)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;

	i = 0;
	while (data->envc[i] && ft_strnstr(data->envc[i], "PATH", 4) == 0)
		i++;
	dir_path = ft_split(data->envc[i] + 5, ':');
	if (!dir_path)
		ft_close_fd(data, "Error: split failed\n");
	i = -1;
	while (dir_path[++i])
	{
		join_path = ft_strjoin(dir_path[i], "/");
		path = ft_strjoin(join_path, cmd);
		free(join_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	ft_free_tab(dir_path);
	return (NULL);
}

void	exec(t_data *data, char *cmd)
{
	char	*path;
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		ft_free_tab(cmd_split);
		ft_close_fd(data, "no cmd");
	}
	path = ft_path(cmd_split[0], data);
	if (!path)
	{
		ft_printf("Command '%s'", cmd_split[0]);
		ft_free_tab(cmd_split);
		ft_close_fd(data, " not found\n");
	}
	if (execve(path, cmd_split, data->envc) == -1)
	{
		ft_free_tab(cmd_split);
		ft_close_fd(data, "execve fail\n");
	}
}

void	ft_process_infile(char *cmd, t_data *data, bool redir)
{
	int	fd_in;

	if (redir == true)
	{
		fd_in = open(cmd, O_RDONLY);
		if (fd_in == -1)
			ft_close_fd(data, "Error opening fd_in");
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			ft_close_fd(data, "Error redirecting stdout");
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_close_fd(data, "Error redirecting stdin");
		close(data->fd[0]);
		close(data->fd[1]);
		close(fd_in);
	}
	exec(data, cmd);
	exit(EXIT_SUCCESS);
}

void	ft_process_outfile(char *cmd, t_data *data)
{
	int	fd_out;

	fd_out = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		ft_close_fd(data, "Error opening fd_out\n");
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		ft_close_fd(data, "Error redirecting stdin\n");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_close_fd(data, "Error redirecting stdout\n");
	close(data->fd[0]);
	close(data->fd[1]);
	close(fd_out);
	exec(data, cmd);
}
