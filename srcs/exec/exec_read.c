#include "minishell.h"

void	count_levels(t_ast_node *node, int level, t_data *data)
{
	if (!node)
		return ;
	data->nb_levels = level;
	if (node->left)
		count_levels(node->left, level + 1, data);
	if (node->right)
		count_levels(node->right, level + 1, data);
}

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

// void	read_ast(t_ast_node *node, t_data *data)
// {
// 	if (!node)
// 		return ;
// 	if (node->type == NODE_PIPE)
// 	{
// 		read_ast(node->left, data);
// 			if (!data->heredoc)
// 				read_ast(node->right, data);
// 	}
// 	else
// 		read_command(node, data);

// }

void	ft_execution(t_data *data)
{
	if (!data->ast)
		return ;
	signal(SIGQUIT, sigquit_handler);
	count_levels(data->ast, 0, data);
	
	if (data->nb_levels == 0)
		no_pipe(data->ast, data);
	//read_ast(data->ast, 0, 0, data);
	wait_commands(data);	
}