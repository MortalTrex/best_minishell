
#include "minishell.h"

// tests : ./minishell infile "ls -l" "wc -l" outfile
//  ./minishell infile "grep a1" "wc -w" outfile

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	dir_path = ft_split(envp[i] + 5, ':');
	if (!dir_path)
		ft_perror_msg("Error: split failed", NULL);
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

void	exec(char *arg, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, 32);
	if (!cmd || !cmd[0])
		ft_perror_msg("Error: empty command", NULL);
	path = find_path(cmd[0], envp);
	if (!path || execve(path, cmd, envp) == -1)
	{
		ft_free_tab(cmd);
		ft_perror_msg("Error: command not found", NULL);
	}
}

void	ft_process_infile(char **argv, int *fd, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		ft_perror_msg("Error opening fd_in", fd);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_perror_msg("Error redirecting stdout", fd);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_perror_msg("Error redirecting stdin", fd);
	close(fd[0]);
	close(fd[1]);
	close(fd_in);
	exec(argv[2], envp);
	exit(EXIT_SUCCESS);
}

void	ft_process_outfile(char **argv, int *fd, char **envp, int argc)
{
	int	fd_out;

	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		ft_perror_msg("Error opening fd_out", fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror_msg("Error redirecting stdin", fd);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_perror_msg("Error redirecting stdout", fd);
	close(fd[0]);
	close(fd[1]);
	close(fd_out);
	exec(argv[3], envp);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (pipe(fd) == -1)
// 		ft_perror_msg("Error creating pipe", NULL);
// 	pid = fork();
// 	if (pid == -1)
// 		ft_perror_msg("Error forking", NULL);
// 	if (pid == 0)
// 		ft_process_infile(argv, fd, envp);
// 	if (pid != 0)
// 		ft_process_outfile(argv, fd, envp, argc);
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid, NULL, 0);
// 	return (EXIT_SUCCESS);
// }
