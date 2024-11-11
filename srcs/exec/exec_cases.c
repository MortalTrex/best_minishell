#include "minishell.h"
#include <unistd.h>

void	one_pipe(t_ast_node *node, t_data *data)
{
	//pid_t	pid;

	read_ast(node, data);
	// if (pipe(data->fd) == -1)
	// 	ft_error(data, "Error creating pipe");
	// pid = fork();
	// if (pid == -1)
	// 	ft_error(data, "Error forking");
	// if (pid == 0)
	// {
	// 	exit(0);
	// }
	// close(data->fd[0]);
	// close(data->fd[1]);
	// waitpid(pid, NULL, 0);
}

void	no_pipe(t_ast_node *node, t_data *data)
{
	bool 	isoutandin;

	if (ft_detect_builtin(node->argv, data) == true)
		return ;
	else
	{
		if (pipe(data->fd) == -1)
			ft_error(data, "Error creating pipe");
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			isoutandin = false;
			read_infile(node, data, isoutandin);
			//read_outfile(node, data, isoutandin);
			exec(data, node->argv);
			exit(0);
		}
		close(data->fd[0]);
		close(data->fd[1]);
		waitpid(node->pid, NULL, 0);
	}
}
