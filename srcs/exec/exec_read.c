#include "minishell.h"


void    read_commands(t_ast_node *node, t_data *data)
{
	t_ast_node *current;
	int i;

	i = 0;
	current = node;
	if (pipe(data->fd) == -1)
			ft_error(data, "Error creating pipe");
	while (current)
	{
		multi_pipe(current, data, i, data->fd);
		current = current->right;
		i++;
	}
}

void	ft_execution(t_data *data)
{
	if (!data->ast)
		return ;
	count_levels(data->ast, 0, data);
	read_redirs(data->ast, data);
	data->stdin_backup = dup(STDIN_FILENO);
    data->stdout_backup = dup(STDOUT_FILENO);
	if (data->stdin_backup == -1 || data->stdout_backup == -1)
    	ft_error(data, "Error backing up stdin/stdout");
	if (data->isheredoc == true)
		ft_process_heredoc(data->ast->redir, data);
	if (data->isheredoc == false)
		if (data->nb_levels == 0)
			no_pipe(data->ast, data);
	transform_ast(data->ast, data);
	//data->count = 0;
	if (data->nb_levels >= 1)
		read_commands(data->new_ast, data);
	close(data->stdin_backup);
    close(data->stdout_backup);
}
