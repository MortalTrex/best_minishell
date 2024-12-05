#include "minishell.h"


void    read_commands(t_ast_node *node, t_data *data)
{
	t_ast_node *current;
	int i;

	i = 0;
	current = node;
	// if (pipe(data->fd) == -1)
	// 		ft_error(data, "Error creating pipe");
	while (current)
	{
		multi_pipe(current, data, i);
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
	if (data->nb_levels == 0)
	{
		no_pipe(data->ast, data);
	}
	transform_ast(data->ast, data);
	if (data->nb_levels >= 1)
		read_commands(data->new_ast, data);
}
