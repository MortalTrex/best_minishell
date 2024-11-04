#include "../inc/minishell.h"

void	print_ast(t_ast_node *node, int level)
{
	t_redir	*redir;
	int		i;
	int		j;

	if (!node)
		return ;
	i = -1;
	while (++i < level)
		printf("  ");
	printf("Node Type: ");
	if (node->type == NODE_CMD)
	{
		printf("Command\n");
		printf("Command: %s\n", node->command);
		printf("Arguments:\n");
		i = -1;
		while (node->argv && node->argv[++i])
		{
			j = -1;
			while (++j < level + 1)
				printf("  ");
			printf("%s\n", node->argv[i]);
		}
		redir = node->redir;
		while (redir)
		{
			i = -1;
			while (++i < level + 1)
				printf("  ");
			printf("Redirection: %s %s\n", redir->file,
				redir->type == IN ? "<" : redir->type == OUT ? ">" :
				redir->type == D_APPEND ? ">>" : "<<");
			redir = redir->next;
		}
	}
	else if (node->type == NODE_PIPE)
		printf("Pipe\n");
	else
		printf("Unknown\n");
	if (node->left)
	{
		i = -1;
		while (++i < level)
			printf("  ");
		printf("Left Child:\n");
		print_ast(node->left, level + 1);
	}
	if (node->right)
	{
		i = -1;
		while (++i < level)
			printf("  ");
		printf("Right Child:\n");
		print_ast(node->right, level + 1);
	}
}

void	print_tab(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
}

