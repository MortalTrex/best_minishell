#include "minishell.h"
#include <unistd.h>

void    multi_pipe(t_ast_node *node, t_data *data, int i)
{
	if (i == 0)
	{
		node->pid = fork();
		if (node->pid == -1)
		ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[0]);
			close(data->fd[1]);
			exec(data, node->argv);
			exit(1);
		}
		waitpid(node->pid, NULL, WNOHANG);
	}
	if (i > 0 && i < data->nb_levels)
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			dup2(data->fd[0], STDIN_FILENO);
			dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[0]);
			close(data->fd[1]);
			exec(data, node->argv);
			exit(1);
		}
		waitpid(node->pid, NULL, 0);
	}
	if (i == data->nb_levels)
	{
		close(data->fd[1]);
		node->pid = fork();
		if (node->pid == -1)
		ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			dup2(data->fd[0], STDIN_FILENO);
			close(data->fd[0]);
			close(data->fd[1]);
			exec(data, node->argv);
			exit(1);
		}
		close(data->fd[0]);
		waitpid(node->pid, NULL, 0);
	}
}

void	one_pipe(t_ast_node *node, t_data *data)
{
	node->pid = fork();
	if (node->pid == -1)
		ft_error(data, "Error forking");
	if (node->pid == 0)
	{
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		exec(data, node->left->argv);
		exit(1);
	}
	waitpid(node->pid, NULL, WNOHANG);
	close(data->fd[1]);
	
	node->pid = fork();
	if (node->pid == -1)
		ft_error(data, "Error forking");
	if (node->pid == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		exec(data, node->right->argv);
		exit(1);
	}
	waitpid(node->pid, NULL, 0);
	close(data->fd[0]);
}

void	no_pipe(t_ast_node *node, t_data *data)
{
	bool 	isoutandin;

	if (ft_detect_builtin(node->argv, data) == true)
		return ;
	else
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			isoutandin = false;
			read_infile(node, data);
			read_outfile(node, data);
			exec(data, node->argv);
			exit(0);
		}
		close(data->fd[0]);
		close(data->fd[1]);
		waitpid(node->pid, NULL, 0);
	}
}
