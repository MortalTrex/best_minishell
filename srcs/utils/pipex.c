/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:46 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/10 17:08:45 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Implementer multi pipe

// tests : ./minishell infile "ls -l" "wc -l" outfile
//  ./minishell infile "grep a1" "wc -w" outfile

// char	*find_path(char *cmd, char **envp, t_data *data)
// {
// 	char	*path;
// 	int		i;
// 	char	**dir_path;
// 	char	*join_path;

// 	i = 0;
// 	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
// 		i++;
// 	dir_path = ft_split(envp[i] + 5, ':');
// 	if (!dir_path)
// 		ft_error(data, "Error: split failed");
// 	i = -1;
// 	while (dir_path[++i])
// 	{
// 		join_path = ft_strjoin(dir_path[i], "/");
// 		path = ft_strjoin(join_path, cmd);
// 		free(join_path);
// 		if (access(path, F_OK) == 0)
// 			return (path);
// 		free(path);
// 	}
// 	ft_free_tab(dir_path);
// 	return (NULL);
// }

// void	exec(char *arg, char **envp, t_data *data)
// {
// 	char	**cmd;
// 	char	*path;

// 	cmd = ft_split(arg, 32);
// 	if (!cmd || !cmd[0])
// 		ft_error(data, "Error: empty command");
// 	path = find_path(cmd[0], envp, data);
// 	if (!path || execve(path, cmd, envp) == -1)
// 	{
// 		ft_free_tab(cmd);
// 		ft_error(data, "Error: command not found");
// 	}
// }

// char	*ft_path(char *cmd, t_data *data)
// {
// 	char	*path;
// 	int		i;
// 	char	**dir_path;
// 	char	*join_path;

// 	i = 0;
// 	while (data->envc[i] && ft_strnstr(data->envc[i], "PATH", 4) == 0)
// 		i++;
// 	dir_path = ft_split(data->envc[i] + 5, ':');
// 	if (!dir_path)
// 		ft_error(data, "Error: split failed");
// 	i = -1;
// 	while (dir_path[++i])
// 	{
// 		join_path = ft_strjoin(dir_path[i], "/");
// 		path = ft_strjoin(join_path, cmd);
// 		free(join_path);
// 		if (access(path, F_OK) == 0)
// 			return (path);
// 		free(path);
// 	}
// 	ft_free_tab(dir_path);
// 	return (NULL);
// }

// void	exec(t_data *data, char *cmd)
// {
// 	char	*path;
// 	char	**cmd_split;

// 	cmd_split = ft_split(cmd, ' ');
// 	if (!cmd_split || !cmd_split[0])
// 	{
// 		ft_free_tab(cmd_split);
// 		ft_error(data, "no cmd");
// 	}
// 	path = ft_path(cmd_split[0], data);
// 	if (!path)
// 	{
// 		ft_free_tab(cmd_split);
// 		ft_error(data, "no path");
// 	}
// 	if (execve(path, cmd_split, data->envc) == -1)
// 	{
// 		ft_free_tab(cmd_split);
// 		ft_error(data, "execve fail");
// 	}
// }

// void	ft_process_infile(char **argv, t_data *data)
// {
// 	// int	fd_in;

// 	// fd_in = open(argv[1], O_RDONLY);
// 	// if (fd_in == -1)
// 	// 	ft_error(data, "Error opening fd_in");
// 	// if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 	// 	ft_error(data, "Error redirecting stdout");
// 	// if (dup2(fd_in, STDIN_FILENO) == -1)
// 	// 	ft_error(data, "Error redirecting stdin");
// 	// close(data->fd[0]);
// 	// close(data->fd[1]);
// 	// close(fd_in);
// 	exec(data, argv[2]);
// 	exit(EXIT_SUCCESS);
// }

// void	ft_process_outfile(char **argv, t_data *data, int argc)
// {
// 	int	fd_out;

// 	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd_out == -1)
// 		ft_error(data, "Error opening fd_out");
// 	if (dup2(data->fd[0], STDIN_FILENO) == -1)
// 		ft_error(data, "Error redirecting stdin");
// 	if (dup2(fd_out, STDOUT_FILENO) == -1)
// 		ft_error(data, "Error redirecting stdout");
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// 	close(fd_out);
// 	exec(data, argv[3]);
// }

// int	exec_launch(int argc, char **argv, t_data *data)
// {
// 	pid_t	pid;

// 	(void)argc;
// 	if (pipe(data->fd) == -1)
// 		ft_error(data, "Error creating pipe");
// 	pid = fork();
// 	if (pid == -1)
// 		ft_error(data, "Error forking");
// 	if (pid == 0)
// 		ft_process_infile(argv, data);
// 	// if (pid != 0)
// 	// 	ft_process_outfile(argv, data, argc);
// 	// close(data->fd[0]);
// 	// close(data->fd[1]);
// 	waitpid(pid, NULL, 0);
// 	return (EXIT_SUCCESS);
// }