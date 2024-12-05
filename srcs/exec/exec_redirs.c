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

void read_heredoc_dup(t_ast_node *node, t_data *data)
{
	t_redir *current;


	current = node->redir;
	while (current)
	{
		if (current->type == D_HEREDOC)
		{
			if (current->hd_fd != -1)
			{
				int fd_in = open(current->file, O_RDONLY);
				if (fd_in == -1)
					ft_close_fd(data, "Error opening fd_in");
				if (dup2(fd_in, STDIN_FILENO) == -1)
					ft_close_fd(data, "Error redirecting stdin");
				if (data->fd[0] != -1)
					close(data->fd[0]);
				if (data->fd[0] != -1)
					close(data->fd[1]);
				close(fd_in);
			}
		}
		current = current->next;
	}
}

int    read_heredoc(t_ast_node *node, t_data *data)
{
	t_redir *current;
	bool in_here_doc = false;

	current = node->redir;
	while (current)
	{
		if (current->type == D_HEREDOC)
		{
			ft_process_heredoc(current, data);
			in_here_doc = true;
		}
		current = current->next;
	}

	return in_here_doc;
}

// void	read_outfile(t_ast_node *node, t_data *data)
// {
// 	t_redir *current;
// 	int	fd_out;

// 	current = node->redir;
// 	while (current)
// 	{
// 		if (current->type == OUT || current->type == D_APPEND)
// 		{
// 			if (current->type == D_APPEND)
// 				fd_out = open(current->file, O_WRONLY | O_CREAT | O_APPEND,
// 					0644);
// 			if (current->type == OUT)
// 				fd_out = open(current->file, O_WRONLY | O_CREAT | O_TRUNC,
// 					0644);
// 			if (fd_out == -1)
// 				ft_close_fd(data, "Error opening fd_out");
// 			if (dup2(fd_out, STDOUT_FILENO) == -1)
// 				ft_close_fd(data, "Error redirecting stdout");
// 			if (data->fd[0] != -1)
// 				close(data->fd[0]);
// 			if (data->fd[0] != -1)
// 				close(data->fd[1]);
// 			close(fd_out);
// 		}
// 		current = current->next;
// 	}
// }

// void	read_infile(t_ast_node *node, t_data *data)
// {
// 	t_redir	*current;
// 	int	fd_in;
// 	char *path = NULL;

// 	current = node->redir;
// 	while (current)
// 	{
// 		if (current->type == IN || current->type == D_HEREDOC)
// 		{
// 			if (current->type == D_HEREDOC)
// 				path = current->file_here_doc;
// 			else
// 				path = current->file;
// 			ft_putstr_fd("File:", 1);
// 			ft_putstr_fd(path, 1);
// 			ft_putstr_fd("\n", 1);
// 			fd_in = open(path, O_RDONLY, 0644);
// 			ft_putstr_fd("Fd:", 1);
// 			ft_putnbr_fd(fd_in, 1);
// 			ft_putstr_fd("\n", 1);
// 			if (fd_in == -1)
// 				ft_close_fd(data, "Error opening fd_in");

// 			if (dup2(fd_in, STDIN_FILENO) == -1)
// 				ft_close_fd(data, "Error redirecting stdin");
// 			if (data->fd[0] != -1)
// 				close(data->fd[0]);
// 			if (data->fd[0] != -1)
// 				close(data->fd[1]);
// 			close(fd_in);
// 		}
// 		current = current->next;
// 	}
// }

void	read_outfile(t_ast_node *node, t_data *data)
{
	t_redir *current;
	int	fd_out;

	current = node->redir;
	while (current)
	{
		if (current->type == OUT || current->type == D_APPEND)
		{
			if (current->type == D_APPEND)
				fd_out = open(current->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (current->type == OUT)
				fd_out = open(current->file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (fd_out == -1)
				ft_close_fd(data, "Error opening fd_out");
			if (dup2(fd_out, STDOUT_FILENO) == -1)
				ft_close_fd(data, "Error redirecting stdout");
			close(data->fd[0]);
			close(data->fd[1]);
			close(fd_out);
		}
		current = current->next;
	}
}

void	read_infile(t_ast_node *node, t_data *data)
{
	t_redir	*current;
	int	fd_in;

	current = node->redir;
	while (current)
	{
		if (current->type == IN)
		{
			fd_in = open(current->file, O_RDONLY);
			if (fd_in == -1)
				ft_close_fd(data, "Error opening fd_in");
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_close_fd(data, "Error redirecting stdin");
			close(data->fd[0]);
			close(data->fd[1]);
			close(fd_in);
		}
		current = current->next;
	}
}

void	read_redirs(t_ast_node *node, t_data *data)
{
	t_redir		*current;

	current = node->redir;
	while (current)
	{
		if (current->type == IN)
			data->isinfile = true;
		if (current->type == OUT || current->type == D_APPEND)
			data->isoutfile = true;
		if (current->type == D_HEREDOC)
			data->isheredoc = true;
		current = current->next;
	}
}