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

void	read_ast(t_ast_node *node, t_data *data)
{
	if (!node)
		return ;
	if (node->argv)
		no_pipe(node, data);
	if (node->type == NODE_PIPE)
	{
		read_ast(node->left, data);
		if (!data->heredoc)
			read_ast(node->right, data);
	}
}

void	ft_execution(t_data *data)
{
	if (!data->ast)
		return ;
	count_levels(data->ast, 0, data);
	if (data->nb_levels == 0)
		no_pipe(data->ast, data);
	if (data->nb_levels == 1)
		one_pipe(data->ast, data);
	if (data->nb_levels > 1)
		one_pipe(data->ast, data);
}