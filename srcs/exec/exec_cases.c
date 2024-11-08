#include "minishell.h"

bool    is_outandin(t_ast_node *node)
{
	t_ast_node *current;
	// bool out;
	// bool in;

	// out = false;
	// in = false;
	current = node;
	while (current->redir != NULL)
	{
		// if (current->redir->type == IN)
		// 	in = true;
		// else if (current->redir->type == OUT)
		// 	out = true;
		current->redir = current->redir->next;
	}
	// if (in == true && out == true)
	// 	return (true);
	return (false);
}

void	read_outfile(t_ast_node *node, t_data *data, bool inout)
{
	int	fd_out;

	node = data->ast;
	while (node->redir)
	{
		if (node->redir->type == OUT)
		{
			fd_out = open(node->redir->file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (fd_out == -1)
				ft_close_fd(data, "Error opening fd_out");
			if (dup2(fd_out, STDOUT_FILENO) == -1)
				ft_close_fd(data, "Error redirecting stdout");
			if (inout == true)
				dup2(data->fd[0], STDIN_FILENO);
			close(data->fd[0]);
			close(data->fd[1]);
			close(fd_out);
		}
		node->redir = node->redir->next;
	}
}

// void	read_infile(t_ast_node *node, t_data *data, bool inout)
// {
// 	t_ast_node	*current;
// 	int	fd_in;

// 	current = node;
// 	while (current->redir)
// 	{
// 		if (current->redir->type == IN)
// 		{
// 			fd_in = open(current->redir->file, O_RDONLY);
// 			if (fd_in == -1)
// 				ft_close_fd(data, "Error opening fd_in");
// 			if (dup2(fd_in, STDIN_FILENO) == -1)
// 				ft_close_fd(data, "Error redirecting stdin");
// 			if (inout == true)
// 				dup2(data->fd[1], STDOUT_FILENO);
// 			close(data->fd[0]);
// 			close(data->fd[1]);
// 			close(fd_in);
// 		}
// 		current->redir = current->redir->next;
// 	}
// }

void	read_infile(t_ast_node *node, t_data *data, bool inout)
{
	t_ast_node	*current;
	int	fd_in;
	(void)inout;

	current = node;
	while (current->redir)
	{
		if (current->redir->type == IN)
		{
			fd_in = open(current->redir->file, O_RDONLY);
			if (fd_in == -1)
				ft_close_fd(data, "Error opening fd_in");
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_close_fd(data, "Error redirecting stdin");
			// if (inout == true)
			// 	dup2(data->fd[1], STDOUT_FILENO);
			// close(data->fd[0]);
			// close(data->fd[1]);
			// close(fd_in);
		}
		current->redir = current->redir->next;
	}
}

void	no_pipe(t_ast_node *node, t_data *data)
{
	pid_t	pid;
	bool 	isoutandin = false;

	// isoutandin = is_outandin(node);
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
			isoutandin = false;
			read_infile(node, data, isoutandin);
			//read_outfile(node, data, isoutandin);
			exec(data, node->argv);
			exit(0);
		}			
		close(data->fd[0]);
		close(data->fd[1]);
		waitpid(pid, NULL, 0);
	}
}
