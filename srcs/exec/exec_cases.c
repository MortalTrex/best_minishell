#include "minishell.h"

int	exec_pipe(char *cmd1, char *cmd2, t_data *data)
{
	pid_t	pid;

	if (pipe(data->fd) == -1)
		ft_close_fd(data, "Error creating pipe\n");
	pid = fork();
	if (pid == -1)
		ft_close_fd(data, "Error forking\n");
	if (pid == 0)
		ft_process_infile(cmd1, data, true);
	if (pid != 0)
		ft_process_outfile(cmd2, data);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

int	exec_onecommand(char *cmd, t_data *data)
{
	pid_t	pid;

	if (pipe(data->fd) == -1)
		ft_close_fd(data, "Error creating pipe\n");
	pid = fork();
	if (pid == -1)
		ft_close_fd(data, "Error forking\n");
	if (pid == 0)
		ft_process_infile(cmd, data, false);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}
