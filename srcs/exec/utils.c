#include "minishell.h"

void	count_levels(t_ast_node *node, int level, t_data *data)
{
	if (!node)
		return ;
	data->nb_levels = level;
	if (node->left)
		count_levels(node->left, level + 1, data);
	if (node->right)
		count_levels(node->right, level + 1, data);
}


void	wait_commands(t_data *data)
{
	signal(SIGINT, SIG_IGN);
	while (errno != ECHILD)
	{
		if (wait(&data->wstatus) == data->last_pid)
		{
			if (WIFEXITED(data->wstatus))
				data->exit_status = WEXITSTATUS(data->wstatus);
			else
			{
				data->exit_status = 128 + WTERMSIG(data->wstatus);
				if (data->exit_status == 131)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				else if (data->exit_status == 139)
					ft_putstr_fd("Segmentation fault (core dumped)\n",
						STDERR_FILENO);
			}
			if (data->exit_status == 130)
				ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	if (g_exit_status == 130)
		data->exit_status = 130;
}

bool	ft_is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}

// void	ft_fds_dup2(t_data *data)
// {
// 	dup2(data->fd[0], 0);
// 	dup2(data->fd[1], 1);
// }

bool	is_builtin(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit"))
		return (true);
	return (false);
}


// void	transform_ast(t_ast_node *node, t_data *data)
// {
// 	(void)node;
// 	(void)data;
// 	int count;

// 	t_ast_node *current_left;
// 	t_ast_node *current;
// 	t_ast_node *new_tree;
// 	t_ast_node *new_tree_head;

// 	current_left = NULL;
// 	current = node;
// 	new_tree = NULL;
// 	new_tree_head = NULL;
// 	count = 0;
// 	while(current)
// 	{
// 		if (count == 0)
// 		{
// 			new_tree = malloc(sizeof(t_ast_node));
// 			if (!new_tree)
// 			{
// 				perror("malloc");
// 				exit(EXIT_FAILURE);
// 			}
// 			ft_memcpy(new_tree, current, sizeof(t_ast_node));
// 			new_tree_head = new_tree;
// 		}
// 		current_left = current->left;

// 		if (current_left && current_left->command != NULL)
// 		{
// 			new_tree->right = malloc(sizeof(t_ast_node));
// 			if (!new_tree->right)
// 			{
// 				perror("malloc");
// 				exit(EXIT_FAILURE);
// 			}
// 			ft_memcpy(new_tree->right, current_left, sizeof(t_ast_node));
// 			new_tree = new_tree->right;
// 		}

// 		if (current && current->command != NULL)
// 		{
// 			new_tree->right = malloc(sizeof(t_ast_node));
// 			if (!new_tree->right)
// 			{
// 				perror("malloc");
// 				exit(EXIT_FAILURE);
// 			}
// 			ft_memcpy(new_tree->right, current, sizeof(t_ast_node));
// 			new_tree = new_tree->right;
// 		}
// 		current = current->right;
// 		count++;
// 	}
// 	new_tree_head = new_tree_head->right;
// 	current = new_tree_head;
// 	while (current)
// 	{
// 		if (current->right)
// 		{
// 			current->right->prev = malloc(sizeof(t_ast_node));
// 			if (!current->right->prev)
// 			{
// 				perror("malloc");
// 				exit(EXIT_FAILURE);
// 			}
// 			ft_memcpy(current->right->prev, current, sizeof(t_ast_node));
// 		}
// 		current = current->right;
// 	}
// 	data->new_ast = new_tree_head;
// }

void	transform_ast(t_ast_node *node, t_data *data)
{
	t_ast_node *current = node;
	t_ast_node *new_tree = NULL;
	t_ast_node **new_tree_ptr = &new_tree;

	while (current)
	{
		if (current->left && current->left->command)
		{
			*new_tree_ptr = malloc(sizeof(t_ast_node));
			if (!*new_tree_ptr)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			ft_memcpy(*new_tree_ptr, current->left, sizeof(t_ast_node));
			new_tree_ptr = &(*new_tree_ptr)->right;
		}

		if (current->command)
		{
			*new_tree_ptr = malloc(sizeof(t_ast_node));
			if (!*new_tree_ptr)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			ft_memcpy(*new_tree_ptr, current, sizeof(t_ast_node));
			new_tree_ptr = &(*new_tree_ptr)->right;
		}

		current = current->right;
	}

	data->new_ast = new_tree;
}