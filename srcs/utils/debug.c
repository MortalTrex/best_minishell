#include "../inc/minishell.h"

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	if (node->type)
	{
		printf("Node Type: ");
		printf("%s\n", node->command);
		if (node->type == NODE_CMD)
		{
			printf("Command: ");
			printf("%s\n", node->command);
			t_redir *redir = node->redir;
			while (redir)
			{
				for (int i = 0; i < level; i++)
					printf("  ");
				printf("Redirection: %s %s\n", redir->command, redir->type == IN ? "<" : redir->type == OUT ? ">"
																				: redir->type == D_APPEND	 ? "<<"
																										: ">>");
				redir = redir->next;
			}
		}
		else if (node->type == NODE_PIPE)
		{
			printf("Pipe\n");
		}
		else
		{
			printf("Unknown Node Type\n");
		}
	}
	if (node->left)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("Left Child:\n");
		print_ast(node->left, level + 1);
	}
	if (node->right)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("Right Child:\n");
		print_ast(node->right, level + 1);
	}
}

void	print_tab(char **str)
{
	if (!str)
		return;
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, str[i], 1);
		i++;
	}
}
