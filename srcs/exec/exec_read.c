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
		multi_pipe(node, data, i);
	if (node->type == NODE_PIPE)
	{
		read_pipe(node->left, data, i++);
		if (data->isheredoc == false)
			read_pipe(node->right, data, i);
	}
}

void	ft_execution(t_data *data)
{
	if (!data->ast)
		return ;
	count_levels(data->ast, 0, data);
	read_redirs(data->ast, data);
	read_redirs(data->ast, data);
	printf("\033[0;31misinfile: %d\n\033[0m", data->isinfile);
	printf("\033[0;31misoutfile: %d\n\033[0m", data->isoutfile);
	printf("\033[0;31misheredoc: %d\n\033[0m", data->isheredoc);
	if (pipe(data->fd) == -1)
		ft_error(data, "Error creating pipe");
	if (data->nb_levels == 0)
		no_pipe(data->ast, data);
	if (data->nb_levels == 1)
		one_pipe(data->ast, data);
	if (data->nb_levels > 1)
		read_pipe(data->ast, data, 0);
}