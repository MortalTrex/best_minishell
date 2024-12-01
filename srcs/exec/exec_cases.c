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

int choose_case_of_dup(int *i, t_data *data)
{
	if (*i == 1 && *i % 2 != 0)
		return (FD_IMPAIR_0);
	if (*i > 1 && *i < data->nb_levels + 1 && *i % 2 != 0)
		return (FD_IMPAIR_MIDDLE);
	if (*i == data->nb_levels && *i % 2 != 0)
		return (FD_IMPAIR_END);
	if (*i > 1 && *i < data->nb_levels + 1 && *i % 2 == 0)
		return (FD_PAIR_MIDDLE);
	if (*i == data->nb_levels + 1 && *i % 2 == 0)
		return (FD_PAIR_END);
	
	return 0;
}

void	multi_pipe(t_ast_node *node, t_data *data, int i)
{
	if (i == 0)
	{
		printf("Case #1: %s\n", node->command);
		printf("Inside multi-pipe: %d\n", data->fd[0]);
		printf("Inside multi-pipe: %d\n", data->fd[1]);
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			read_infile(node, data);
    		read_outfile(node, data);
			if (is_builtin(node->argv[0]) == true)
			{
				ft_detect_builtin(node->argv, data);
				ft_free_all(data);
			}
			else
				exec(data, node->argv);
			exit(1);
		}
		close(data->fd[1]);
	}

	if (i > 0 && i < data->nb_levels)
	{
		printf("Case #3: %s\n", node->command);
		printf("Inside multi-pipe: %d\n", data->fd[0]);
		printf("Inside multi-pipe: %d\n", data->fd[1]);
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			dup2(data->fd[0], STDIN_FILENO);
			// read_infile(node, data);
    		// read_outfile(node, data);
			if (is_builtin(node->argv[0]) == true)
			{
				ft_detect_builtin(node->argv, data);
				ft_free_all(data);
			}
			else
				exec(data, node->argv);
			exit(1);
		}
	}

	if (i == data->nb_levels)
	{
		printf("Case #2: %s\n", node->command);
		printf("Inside multi-pipe: %d\n", data->fd[0]);
		printf("Inside multi-pipe: %d\n", data->fd[1]);
		close(data->fd[1]);
		node->pid = fork();
		if (node->pid == -1)
			ft_error(data, "Error forking");
		if (node->pid == 0)
		{
			dup2(data->fd[0], STDIN_FILENO);
			read_infile(node, data);
    		read_outfile(node, data);
			if (is_builtin(node->argv[0]) == true)
			{
				ft_detect_builtin(node->argv, data);
				ft_free_all(data);
			}
			else
				exec(data, node->argv);
			exit(1);
		}
		close(data->fd[0]);
		waitpid(node->pid, NULL, 0);
	}

	if (dup2(data->stdin_backup, STDIN_FILENO) == -1 || dup2(data->stdout_backup,
            STDOUT_FILENO) == -1)
        ft_error(data, "Error restoring stdin/stdout");
}

void	no_pipe(t_ast_node *node, t_data *data)
{
	if (pipe(data->fd) == -1)
			ft_error(data, "Error creating pipe");
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
