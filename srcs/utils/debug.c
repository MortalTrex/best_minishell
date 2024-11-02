#include "../inc/minishell.h"

void	print_tokens(t_data *data)
{
	t_token	*tmp = data->tok;

	while (tmp)
	{
		if (tmp->type == T_WORD)
			printf("\033[1;32mT_WORD: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_OPERATOR)
			printf("\033[1;34mT_OPERATOR: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_BUILTIN)
			printf("\033[1;35mT_BUILTIN: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_REDIR_APPEND)
			printf("\033[1;37mT_REDIR_APPEND: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_REDIR_HERE)
			printf("\033[1;38mT_REDIR_HERE: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_REDIR_IN)
			printf("\033[1;34mT_REDIR_IN: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_REDIR_OUT)
			printf("\033[1;30mT_REDIR_OUT: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_PIPE)
			printf("\033[1;36mT_PIPE: %s\033[0m\n", tmp->value);
		tmp = tmp->next;
	}
}

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
		write(1, str[i], 1);
		i++;
	}
}
