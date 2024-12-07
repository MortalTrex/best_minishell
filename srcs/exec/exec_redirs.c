#include "minishell.h"

void read_heredoc_dup(t_shell_list *node, t_data *data)
{
	t_redir *current;


	current = node->redir;
	while (current)
	{
		if (current->type == D_HEREDOC)
		{
			if (current->hd_fd != -1)
			{
				int fd_in = open(current->value, O_RDONLY);
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

int    ft_read_heredoc(t_shell_list *node, t_data *data)
{
	t_redir *current;
	bool in_here_doc = false;

	current = node->redir;
	while (current)
	{
		if (current->type == D_HEREDOC)
		{
			ft_process_heredoc(current, data, false);
			in_here_doc = true;
		}
		current = current->next;
	}

	return in_here_doc;
}

void	ft_read_outfile(t_shell_list *node, t_data *data)
{
	t_redir *current;
	int	fd_out;

	current = node->redir;
	while (current)
	{
		if (current->type == OUT || current->type == D_APPEND)
		{
			if (current->type == D_APPEND)
				fd_out = open(current->value, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (current->type == OUT)
				fd_out = open(current->value, O_WRONLY | O_CREAT | O_TRUNC,
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

void	ft_read_infile(t_shell_list *node, t_data *data, bool in_multipipe)
{
	t_redir	*current;
	int		fd_in;

	(void)in_multipipe;

	current = node->redir;
	while (current)
	{
		if (current->type == IN)
		{
			fd_in = open(current->value, O_RDONLY);
			if (fd_in == -1)
				ft_error(data, "Error opening input file");
			if (dup2(fd_in, STDIN_FILENO) == -1)
			{
				close(fd_in);
				ft_error(data, "Error redirecting stdin");
			}
			close(fd_in);
		}
		else if (current->type == D_HEREDOC)
		{
			printf("ENTER HERE DOC\n");
			fd_in = open(current->file_here_doc, O_RDONLY);
			if (fd_in == -1)
				ft_error(data, "Error opening heredoc file");
			if (dup2(fd_in, STDIN_FILENO) == -1)
			{
				close(fd_in);
				ft_error(data, "Error redirecting stdin");
			}
			close(fd_in);
		}
		current = current->next;
	}
}


void	ft_read_redirs(t_shell_list *node, t_data *data)
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
