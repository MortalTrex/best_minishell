#include "minishell.h"

// int	ft_process_redirections(t_ast_node *node)
// {
// 	t_redir	*redirs;
// 	int		status;

// 	redirs = node->redir;
// 	while(redirs)
// 	{
// 		if (redirs->type == T_REDIR_IN)
// 			return(ft_process_infile(redirs));
// 		else if (redirs->type == T_REDIR_OUT)
// 			return(ft_process_outfile(redirs));
// 		else if (redirs->type == T_REDIR_APPEND)
// 			return(ft_process_append(redirs));
// 		else if(redirs->type == T_REDIR_HERE)
// 			(dup2(redirs->hd_fd, 0), close(redirs->hd_fd));
// 		redirs = redirs->next;
// 	}
// 	return (1); // handle error statuses
// }

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

void	read_infile(t_ast_node *node, t_data *data, bool inout)
{
	t_ast_node	*current;
	int	fd_in;

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
			if (inout == true)
				dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[0]);
			close(data->fd[1]);
			close(fd_in);
		}
		current->redir = current->redir->next;
	}
}