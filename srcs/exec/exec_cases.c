#include "minishell.h"

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
	//pid_t	pid;
	if (ft_detect_builtin(node->argv, data) == true)
		return ;
	// else
	// {
	// 	if (pipe(data->fd) == -1)
	// 		ft_error(data, "Error creating pipe");
	// 	pid = fork();
	// 	if (pid == -1)
	// 		ft_error(data, "Error forking");
	// 	if (pid == 0)
	// 	{
	// 		read_infile(node, data);
	// 		exec(data, node->argv);
	// 		read_outfile(node, data);
	// 	}
	// 	// if (pid != 0)
	// 	// {
	// 	// 	read_outfile(node, data);
	// 	// }			
	// 	close(data->fd[0]);
	// 	close(data->fd[1]);
	// 	waitpid(pid, NULL, 0);
	// }
}
