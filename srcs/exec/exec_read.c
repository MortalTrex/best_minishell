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
		if (ft_detect_builtin(node->argv, data) == true)
			return ;
		else
		{
			exec_onecommand(node->argv, data);
			while (node->argv && node->argv[i])
			{
				printf("\033[0;32m%s\033[0m\n", node->argv[i]);
				i++;
			}
		}
	}
	if (node->left)
		read_ast(node->left, level + 1, count, data);
	if (node->right)
		read_ast(node->right, level + 1, count + 1, data);
}
