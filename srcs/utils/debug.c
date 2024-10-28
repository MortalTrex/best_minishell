#include "../inc/minishell.h"

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	while (node->type)
	{
		if (node->type == NODE_CMD)
		{
			printf("Command: ");
			print_tab(node->cmd->argv);
			printf("\n");
			t_redir *redir = node->cmd->redir;
			while (redir)
			{
				for (int i = 0; i < level; i++)
					printf("  ");
				printf("Redirection: %s %s\n", redir->file, redir->type == IN ? "<" : redir->type == OUT ? ">"
																				: redir->type == D_APPEND	 ? "<<"
																										: ">>");
				redir = redir->next;
			}
			break;
		}
		else if (node->type == NODE_PIPE)
		{
			printf("Pipe\n");
			break;
		}
		else if (node->type ==NODE_REDIR_IN)
		{
			printf("Redirection In: %s\n", node->file);
			break;
		}
		else if (node->type ==NODE_REDIR_OUT)
		{
			printf("Redirection Out: %s\n", node->file);
			break;
		}
		else if (node->type ==NODE_REDIR_APPEND)
		{
			printf("Redirection Append: %s\n", node->file);
			break;
		}
		else if (node->type ==NODE_HEREDOC)
		{
			printf("Heredoc: %s\n", node->file);
			break;
		}
		else
		{
			printf("Unknown Node Type\n");
			break;
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