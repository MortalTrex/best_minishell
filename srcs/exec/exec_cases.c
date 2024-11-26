#include "minishell.h"
#include <unistd.h>

// void	multi_pipe(t_ast_node *node, t_data *data, int i)
// {
// 	if (i == data->nb_levels)
// 	{
// 		close(data->fd[1]);
// 		close(data->fd[0]);
// 	}
// 	node->pid = fork();
// 	if (node->pid == -1)
// 		ft_error(data, "Error forking");
// 	if (node->pid == 0)
// 	{
// 		if (i > 0)
// 			dup2(data->fd[0], STDIN_FILENO);
// 		if (i >= 0 && i < data->nb_levels)
// 			dup2(data->fd[1], STDOUT_FILENO);
// 		close(data->fd[0]);
// 		close(data->fd[1]);
// 		if (is_builtin(node->argv[0]) == true)
// 			ft_detect_builtin(node->argv, data);
// 		else
// 		if (i == data->nb_levels)
// 		{
// 			close(data->fd[0]);
// 			close(data->fd[1]);
// 		}
// 	}
// 	if (i == data->nb_levels)
// 		close(data->fd[0]);
// 	if (i == 0)
// 		waitpid(node->pid, NULL, 1);
// 	if (i > 0)
// 		waitpid(node->pid, NULL, 0);
// 	if (dup2(data->stdin_backup, STDIN_FILENO) == -1 || dup2(data->stdout_backup,
//             STDOUT_FILENO) == -1)
//         ft_error(data, "Error restoring stdin/stdout");
// }

void	multi_pipe(t_ast_node *node, t_data *data, int i)
{
	read_infile(node, data);
    read_outfile(node, data);
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
			close(data->stdin_backup);
			close(data->stdout_backup);
			exec(data, node->argv);
			exit(1);
		}
		waitpid(node->pid, NULL, 1);
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
		close(data->fd[1]);
		waitpid(node->pid, NULL, 0);
	}

	if (dup2(data->stdin_backup, STDIN_FILENO) == -1 || dup2(data->stdout_backup,
            STDOUT_FILENO) == -1)
        ft_error(data, "Error restoring stdin/stdout");
}

void	no_pipe(t_ast_node *node, t_data *data)
{
    read_infile(node, data);
    read_outfile(node, data);
    if (is_builtin(node->argv[0]))
        ft_detect_builtin(node->argv, data);
    else
    {
        node->pid = fork();
        if (node->pid == -1)
            ft_error(data, "Error forking");
        if (node->pid == 0)
        {
            close(data->fd[0]);
            close(data->fd[1]);
            close(data->stdin_backup);
            close(data->stdout_backup);
            exec(data, node->argv);
            exit(1);
        }
        waitpid(node->pid, NULL, 0);
    }
    if (dup2(data->stdin_backup, STDIN_FILENO) == -1 || dup2(data->stdout_backup,
            STDOUT_FILENO) == -1)
        ft_error(data, "Error restoring stdin/stdout");
    close(data->fd[0]);
    close(data->fd[1]);
}
