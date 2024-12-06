#include "minishell.h"

// static void	read_command(t_ast_node *node, t_data *data)
// {
// 	t_redir	*redirs;

// 	redirs = node->redir;
// 	while (redirs)
// 	{
// 		if (redirs->type == D_HEREDOC)
// 			ft_process_heredoc(redirs, data);
// 		else
// 			redirs->argv = ft_expand_and_clean(redirs->file, data);
// 		redirs = redirs->next;
// 	}
// }

void	read_pipe(t_ast_node *node, t_data *data, int i)
{
	if (!node)
		return ;
	if (node->argv)
	{
		multi_pipe(node, data, i);
		// close(data->stdin_backup);
    	// close(data->stdout_backup);
	}
	if (node->type == NODE_PIPE)
	{
		read_pipe(node->left, data, i++);
		if (data->isheredoc == false)
			read_pipe(node->right, data, i);
	}
}

void	ft_execution(t_data *data)
{
	if (!data->shell_list)
		return ;
	count_levels(data->shell_list, 0, data);
	printf("data->levels: %d", data->nb_levels);
	exit(0);
	read_redirs(data->ast, data);
	data->stdin_backup = dup(STDIN_FILENO);
    data->stdout_backup = dup(STDOUT_FILENO);
	if (data->stdin_backup == -1 || data->stdout_backup == -1)
    	ft_error(data, "Error backing up stdin/stdout");
	if (pipe(data->fd) == -1)
		ft_error(data, "Error creating pipe");
	if (data->isheredoc)
		read_heredoc(data->ast, data);
	if (data->isheredoc == false)
		if (data->nb_levels == 0)
			no_pipe(data->ast, data);
	// if (data->nb_levels == 1)
	// 	one_pipe(data->ast, data);
	if (data->nb_levels >= 1)
		read_pipe(data->ast, data, 0);
	close(data->stdin_backup);
    close(data->stdout_backup);
}
