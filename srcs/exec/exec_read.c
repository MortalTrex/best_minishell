#include "minishell.h"

void	read_ast(t_ast_node *node, int level, int count, t_data *data)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	printf("\033[0;31mlevel: %d\033[0m\n", count);
	if (node->type == NODE_CMD)
	{
		ft_detect_builtin(node->argv, data);
		while (node->argv && node->argv[i])
		{
			printf("\033[0;32m%s\033[0m\n", node->argv[i]);
			i++;
		}
	}
	if (node->left)
		read_ast(node->left, level + 1, count, data);
	if (node->right)
		read_ast(node->right, level + 1, count + 1, data);
}

void	ft_execution(t_data *data)
{
	t_ast_node	*current;
	int	i;

	i = 0;
	current = data->ast;
	if (current != NULL)
		read_ast(current, 0, 0, data);
	// while (current)
	// {
	// 	if (current->type == T_WORD && i == 0)
	// 	{
	// 		if (exec_onecommand(current->value, data) == -1)
	// 			ft_error(data, "Error: exec failed\n");
	// 		cmd = ft_strdup(current->value);
	// 	}
	// 	if (current-> type == T_PIPE)
	// 	{
	// 		printf("current->value: %s\n", current->value);
	// 		exec_pipe(cmd, current->next->value, data);
	// 		free(cmd);
	// 	}
	// 	if (current)
	// 		current = current->next;
	// 	i++;
	// }
}
