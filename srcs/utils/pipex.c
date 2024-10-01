/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:46 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/01 15:51:31 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Implementer multi pipe
//

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

// void	ft_process_infile(char **argv, char **envp, t_data *data)
// {
// 	int	fd_in;

// 	fd_in = open(argv[1], O_RDONLY);
// 	if (fd_in == -1)
// 		ft_error(data, "Error opening fd_in");
// 	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 		ft_error(data, "Error redirecting stdout");
// 	if (dup2(fd_in, STDIN_FILENO) == -1)
// 		ft_error(data, "Error redirecting stdin");
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// 	close(fd_in);
// 	exec(argv[2], envp, data);
// 	exit(EXIT_SUCCESS);
// }

// void	ft_process_outfile(char **argv, t_data *data, char **envp, int argc)
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
// 	exec(argv[3], envp, data);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (pipe(fd) == -1)
// 		ft_error("Error creating pipe", NULL);
// 	pid = fork();
// 	if (pid == -1)
// 		ft_error("Error forking", NULL);
// 	if (pid == 0)
// 		ft_process_infile(argv, fd, envp);
// 	if (pid != 0)
// 		ft_process_outfile(argv, fd, envp, argc);
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid, NULL, 0);
// 	return (EXIT_SUCCESS);
// }
