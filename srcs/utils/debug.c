#include "../inc/minishell.h"

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");

	printf("Node Type: ");
	switch (node->type)
	{
		case NODE_CMD:
			printf("Command\n");
			printf("  Command: %s\n", node->command);
			printf("  Arguments:\n");
			for (int i = 0; node->argv && node->argv[i]; i++)
			{
				for (int j = 0; j < level + 1; j++)
					printf("  ");
				printf("%s\n", node->argv[i]);
			}
			t_redir *redir = node->redir;
			while (redir)
			{
				for (int i = 0; i < level + 1; i++)
					printf("  ");
				printf("Redirection: %s %s\n", redir->command, redir->type == IN ? "<" : redir->type == OUT	   ? ">"
																					: redir->type == D_APPEND ? ">>"
																											: "<<");
				redir = redir->next;
			}
			break;
		case NODE_PIPE:
			printf("Pipe\n");
			break;
		default:
			printf("Unknown\n");
			break;
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

void print_tab(char **str)
{
	if (!str)
		return;
	int i;

	i = 0;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
}
