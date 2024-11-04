#include "minishell.h"

int	exec_onecommand(char **cmd, t_data *data)
{
	pid_t	pid;

	if (pipe(data->fd) == -1)
		ft_close_fd(data, "Error creating pipe\n");
	pid = fork();
	if (pid == -1)
 		ft_close_fd(data, "Error forking\n");
	if (pid == 0)
		exec(data, cmd);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

void no_pipe(t_ast_node *node, t_data *data)
{
	int fd_in;

	node = data->ast;
	while(node->redir)
	{
		if (node->redir->type == IN)
		{
			fd_in = open(node->redir->file, O_RDONLY);
			if (fd_in == -1)
				ft_close_fd(data, "Error opening fd_in");
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_close_fd(data, "Error redirecting stdin");
			close(data->fd[0]);
			close(data->fd[1]);
			close(fd_in);
		}
		node->redir = node->redir->next;
	}
	if (ft_detect_builtin(node->argv, data) == true)
		return ;
	else
		exec_onecommand(node->argv, data);
}

// int	exec_pipe(char *cmd1, char *cmd2, t_data *data)
// {
// 	pid_t	pid;

// 	if (pipe(data->fd) == -1)
// 		ft_close_fd(data, "Error creating pipe\n");
// 	pid = fork();
// 	if (pid == -1)
// 		ft_close_fd(data, "Error forking\n");
// 	if (pid == 0)
// 		ft_process_infile(cmd1, data, true);
// 	if (pid != 0)
// 		ft_process_outfile(cmd2, data);
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// 	waitpid(pid, NULL, 0);
// 	return (EXIT_SUCCESS);
// }
