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

	i = 0;
	if (!node)
		return ;
	printf("\033[0;31mlevel: %d\033[0m\n", count);
	if (node->type == NODE_CMD)
	{
		if (ft_detect_builtin(node->argv, data) == true)
			return ;
		else
		{
			if (count == 0)
				exec_onecommand(node->argv, data);
			if (count > 0)
				printf("Plein de pipes\n");
		}
	}
	if (node->left)
		read_ast(node->left, level + 1, count, data);
	if (node->right)
		read_ast(node->right, level + 1, count + 1, data);
}
