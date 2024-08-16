#include "../inc/minishell.h"

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
void	ft_pipe(char *arg, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, ' ');
	path = find_path(cmd[0], envp);
}

void	ft_process_child(char **argv, int *fd, char **envp)
{
	int	input_file;

	input_file = open (argv[1], O_RDONLY);
	close(fd[0]);
	close(fd[1]);
	close(input_file);
	ft_pipe(argv[2], envp);
	exit (EXIT_SUCCESS);
}

void	ft_process_parent(char **argv, int *fd, char **envp)
{
	int	output_file;

	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd[0]);
	close(fd[1]);
	close(output_file);
	ft_pipe(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;

    if (argc != 5)
    {
        ft_putstr_fd("Error: Wrong number of arguments\n", 2);
        return (EXIT_FAILURE);
    }
	pid = fork();
	if (pid == 0)
		ft_process_child(argv, fd, envp);
	pid2 = fork();
	if (pid2 == 0)
		ft_process_parent(argv, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (EXIT_SUCCESS);
}