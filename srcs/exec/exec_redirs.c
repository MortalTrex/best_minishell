#include "minishell.h"


void	ft_process_infile(char **cmd, t_data *data)
{
	int	fd_in;

	fd_in = open(cmd[0], O_RDONLY);
	if (fd_in == -1)
		ft_close_fd(data, "Error opening fd_in");
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		ft_close_fd(data, "Error redirecting stdout");
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_close_fd(data, "Error redirecting stdin");
	close(data->fd[0]);
	close(data->fd[1]);
	close(fd_in);
	exec(data, cmd);
	exit(EXIT_SUCCESS);
}

int ft_process_redirections(t_ast_node *node, t_data *data)
{
	t_redir	*redirs;

	redirs = node->redir;
	while(redirs)
	{
		if (redirs->type == T_REDIR_IN)
			ft_process_infile(node->argv, data);
		// else if (redirs->type == T_REDIR_OUT)
		// 	return(ft_process_outfile(redirs));
		// else if (redirs->type == T_REDIR_APPEND)
		// 	return(ft_process_append(redirs));
		// else if(redirs->type == T_REDIR_HERE)
		// 	(dup2(redirs->hd_fd, 0), close(redirs->hd_fd));
		redirs = redirs->next;
	}
	return (1); // handle error statuses
}


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
