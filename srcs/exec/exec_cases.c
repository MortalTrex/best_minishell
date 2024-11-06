#include "minishell.h"

// static void ft_exec_pipe_child(t_ast_node *node, int pfds[2], bool isleft, t_data *data)
// {
// 	int	status;

// 	if (isleft)
// 	{
// 		close(pfds[0]);
// 		dup2(pfds[1], STDOUT_FILENO);
// 		close(pfds[1]);
// 	}
// 	else
// 	{
// 		close(pfds[1]);
// 		dup2(pfds[0], STDIN_FILENO);
// 		close(pfds[0]);
// 	}
// 	status = exec_node(node, data, true);
// 	(ft_free_all(&data), exit(status));
// }

// int	exec_pipe(t_ast_node *node, t_data *data)
// {
// 	int		fds[2];
// 	int		left;
// 	int		right;
// 	int		status;

// 	pipe(fds);
// 	left = fork();
// 	if (left == -1)
// 		(perror("fork"), exit(EXIT_FAILURE));
// 	data->last_pid = left;
// 	if (!left)
// 		ft_exec_pipe_child(node->left, data, fds, true);
// 	else
// 	{
// 		right = fork();
// 		if (right == -1)
// 			(perror("fork"), exit(EXIT_FAILURE));
// 		data->last_pid = right;
// 		if (!right)
// 			ft_exec_pipe_child(node->right, data, fds, false);
// 		else
// 		{
// 			close(fds[0]);
// 			close(fds[1]);
// 			waitpid(left, &status, 0);
// 			waitpid(right, &status, 0);
// 			return(status);
// 		}
// 	}
// 	return (ERRGEN);
// }

// int	exec_node(t_ast_node *node, t_data *data, bool ispipe)
// {
// 	if (!node)
// 		return (EXIT_FAILURE);
// 	if (node->type == NODE_PIPE)
// 		return (exec_pipe(node, data));
// 	else
// 		return (exec_onecommand(node, data, ispipe));
// 	return (ERRGEN);
// }

void	read_outfile(t_ast_node *node, t_data *data)
{
	int	fd_out;

	node = data->ast;
	while (node->redir->type == OUT)
	{
		fd_out = open(node->redir->file, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (fd_out == -1)
			ft_close_fd(data, "Error opening fd_out");
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			ft_close_fd(data, "Error redirecting stdout");
		close(data->fd[0]);
		close(data->fd[1]);
		close(fd_out);
		node->redir = node->redir->next;
	}
}

void	read_infile(t_ast_node *node, t_data *data)
{
	int	fd_in;

	node = data->ast;
	while (node->redir)
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
}

void	no_pipe(t_ast_node *node, t_data *data)
{
	pid_t	pid;
	if (ft_detect_builtin(node->argv, data) == true)
		return ;
	else
	{
		if (pipe(data->fd) == -1)
			ft_error(data, "Error creating pipe");
		pid = fork();
		if (pid == -1)
			ft_error(data, "Error forking");
		if (pid == 0)
		{
			read_infile(node, data);
			exec(data, node->argv);
			read_outfile(node, data);
		}
		// if (pid != 0)
		// {
		// 	read_outfile(node, data);
		// }			
		close(data->fd[0]);
		close(data->fd[1]);
		waitpid(pid, NULL, 0);
	}
}
