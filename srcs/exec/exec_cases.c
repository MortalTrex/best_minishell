#include "minishell.h"
#include <unistd.h>


// int	choose_case_of_dup(int *i, t_data *data)
// {
// 	if (*i == 1 && *i % 2 != 0)
// 		return (FD_IMPAIR_0);
// 	if (*i > 1 && *i < data->nb_levels + 1 && *i % 2 != 0)
// 		return (FD_IMPAIR_MIDDLE);
// 	if (*i == data->nb_levels && *i % 2 != 0)
// 		return (FD_IMPAIR_END);
// 	if (*i > 1 && *i < data->nb_levels + 1 && *i % 2 == 0)
// 		return (FD_PAIR_MIDDLE);
// 	if (*i == data->nb_levels + 1 && *i % 2 == 0)
// 		return (FD_PAIR_END);
// 	return (0);
// }

void	multi_pipe(t_ast_node *node, t_data *data, int i)
{
	pid_t	pid;

	if (i < data->nb_levels && pipe(data->pipe_fd) == -1)
		ft_error(data, "Error creating pipe");
	pid = fork();
	if (pid == -1)
		ft_error(data, "Error forking");
	
	if (pid == 0)
	{
		// bool in_here_doc = false;
		
		// if (read_heredoc(node, data))
		// {
		// 	in_here_doc = true;
		// }

		read_heredoc(node, data);
		if (i > 0)
		{
			dup2(data->fd[0], STDIN_FILENO);
			close(data->fd[0]);
		}
		if (i < data->nb_levels)
		{
			dup2(data->pipe_fd[1], STDOUT_FILENO);
			close(data->pipe_fd[1]);
		}
		close(data->pipe_fd[0]);
		read_infile(node, data);
		read_outfile(node, data);

		// printf("in here doc: %d\n", in_here_doc);
		// if (in_here_doc == true)
		// {
		// 	read_heredoc_dup(node, data);
		// }
		// in_here_doc = false;
		
		
		
		if (is_builtin(node->argv[0]) == true)
		{
			ft_detect_builtin(node->argv, data);
			ft_free_all(data);
		}
		else
			exec(data, node->argv);
		exit(1);
	}
	if (i > 0)
		close(data->fd[0]);
	if (i < data->nb_levels)
	{
		data->fd[0] = data->pipe_fd[0];
		data->fd[1] = data->pipe_fd[1];
		close(data->pipe_fd[1]);
	}
	if (i == data->nb_levels)
	{
		close(data->fd[0]);
		waitpid(pid, NULL, 0);
	}
}


void	no_pipe(t_ast_node *node, t_data *data)
{
	// bool in_here_doc = false;
	
	// data->stdin_backup = dup(STDIN_FILENO);
    // data->stdout_backup = dup(STDOUT_FILENO);
	// if (data->stdin_backup == -1 || data->stdout_backup == -1)
    // 	ft_error(data, "Error backing up stdin/stdout");
	// if (pipe(data->fd) == -1)
	// 	ft_error(data, "Error creating pipe");

	
	// if (read_heredoc(data->ast, data))
	// 	in_here_doc = true;
	
	// if (in_here_doc == true)
	// {
	// 	read_heredoc_dup(node, data);
	// }
	// in_here_doc = false;
		
	
	if (node && node->argv && is_builtin(node->argv[0]))
		ft_detect_builtin(node->argv, data);
	else
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			read_heredoc(node, data);

			// dup2(data->fd[0], STDIN_FILENO);
			// dup2(data->fd[1], STDOUT_FILENO);

			

			read_infile(node, data);
			read_outfile(node, data);



			// close(data->fd[0]);
			// close(data->fd[1]);
			// close(data->stdin_backup);
			// close(data->stdout_backup);
			exec(data, node->argv);
			exit(1);
		}
		waitpid(node->pid, NULL, 0);
	}
	// if (dup2(data->stdin_backup, STDIN_FILENO) == -1
	// 	|| dup2(data->stdout_backup, STDOUT_FILENO) == -1)
	// 	ft_error(data, "Error restoring stdin/stdout");
	// close(data->fd[0]);
	// close(data->fd[1]);
	// close(data->stdin_backup);
    // close(data->stdout_backup);
}
