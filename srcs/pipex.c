#include "../inc/minishell.h"

// tests : ./minishell infile "ls -l" "wc -l" outfile
//  ./minishell infile "grep a1" "wc -w" outfile


void	ft_perror_msg(char *msg, int *fd)
{
	if (fd != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	perror(msg);
	exit(EXIT_FAILURE);
}
//This function will be used to find the path of the command in the PATH environment variable.
char	*find_path(char *cmd, char **envp)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;

	i = 0;
	//We will loop through the environment variables to find the PATH variable.
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	//Dir path will be an array of strings containing the different paths in the PATH variable.
	dir_path = ft_split(envp[i] + 5, ':');
	i = -1;
	//We will loop through the different paths to find the command.
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

//This function will be used to execute the command in the child process.
void	ft_pipe(char *arg, char **envp)
{
	char	**cmd;
	char	*path;

	//We will split the command to get the command and its arguments. (ex: ls -l)
	cmd = ft_split(arg, ' ');
	if (!cmd || !cmd[0])
	{
		ft_free_tab(cmd);
		ft_perror_msg("Error: empty command", NULL);
	}
	//We will find the path of the command.
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_free_tab(cmd);
		ft_perror_msg("Error: command not found", NULL);
	}
	//We will execute the command.
	if (execve(path, cmd, envp) == -1)
	{
		ft_free_tab(cmd);
		ft_perror_msg("Error: execve failed", NULL);
	}
}
//This function will be used to execute the command in the child process.
// It's the same for argv[2] (combined to input) and argv[3] (combined to output).
// inout == 0 means that the command is combined to the input file; inout == 1 means that the command is combined to the output file.
void	ft_process(char **argv, int *fd, char **envp, int inout)
{
	int	file;
	int nb;

	nb = 0;
	if (inout == 0)
	{
		nb = 1;
		file = open(argv[1], O_RDONLY);
	}
	else
		file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		ft_perror_msg("Error opening input_file", fd);
	if (dup2(fd[nb], nb) == -1)
		ft_perror_msg("Error redirecting stdin", fd);
	if (dup2(file, nb) == -1)
		ft_perror_msg("Error redirecting stdout", fd);
	close(fd[0]);
	close(fd[1]);
	close(file);
	ft_pipe(argv[3 - nb], envp);
	if (inout == 0)
		exit(EXIT_SUCCESS);
}

void	ft_process_child(char **argv, int *fd, char **envp)
{
	int	input_file;

	input_file = open (argv[1], O_RDONLY);
	if (input_file == -1)
	{
		ft_perror_msg("Error opening input_file", fd);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_perror_msg("Error redirecting stdout", fd);
	if (dup2(input_file, STDIN_FILENO) == -1)
		ft_perror_msg("Error redirecting stdin", fd);
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
	if (output_file == -1)
		ft_perror_msg("Error opening output_file", fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror_msg("Error redirecting stdin", fd);
	if (dup2(output_file, STDOUT_FILENO) == -1)
		ft_perror_msg("Error redirecting stdout", fd);
	close(fd[0]);
	close(fd[1]);
	close(output_file);
	ft_pipe(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int fd[2];
	pid_t pid;
	pid_t pid2;

	(void)argc;
	if (pipe(fd) == -1)
		ft_perror_msg("Error creating pipe", NULL);
	pid = fork();
	if (pid == -1)
		ft_perror_msg("Error forking", NULL);
	if (pid == 0)
		ft_process(argv, fd, envp, 0);
	pid2 = fork();
	if (pid2 == -1)
		ft_perror_msg("Error forking", NULL);
	if (pid2 == 0)
		ft_process(argv, fd, envp, 1);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (EXIT_SUCCESS);
}