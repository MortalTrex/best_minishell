#include "minishell.h"

void	count_levels(t_ast_node *node, int level)
{
	if (!node)
		return ;
	node->nb_levels = level;
	if (node->left)
		count_levels(node->left, level + 1);
	if (node->right)
		count_levels(node->right, level + 1);
}

void	read_ast(t_ast_node *node, int level, int count, t_data *data)
{
	int	i;
	pid_t pid;

	i = 0;
	if (!node)
		return ;
	(void)data;
	level = 0;
	printf("\033[0;31mlevel: %d\033[0m\n", count);
	if (node->type == NODE_CMD)
	{
		if (pipe(data->fd) == -1)
			ft_close_fd(data, "Error creating pipe\n");
		pid = fork();
		if (pid == -1)
			ft_close_fd(data, "Error forking\n");
		if (ft_detect_builtin(node->argv, data) == true)
		{
			if (pid == 0)
			 	exit(0);
			close(data->fd[0]);
			close(data->fd[1]);
			waitpid(pid, NULL, 0);
			return ;
		}
		else
		{
			if (level == 0)
				exec_onecommand(node->argv, pid, data);
			// else
			// 	exec_pipe(data, node->argv);
		}
	}
	if (node->left)
		read_ast(node->left, level + 1, count, data);
	if (node->right)
		read_ast(node->right, level + 1, count + 1, data);
}
void	ft_execution(t_data *data)
{
	count_levels(data->ast, 0);
	if (data->nb_levels == 0)
		no_pipe(data->ast->argv, 0, data);
	//read_ast(data->ast, 0, 0, data);

}