#include "minishell.h"

// static void	read_command(t_ast_node *node, t_data *data)
// {
// 	t_redir	*redirs;

// 	redirs = node->redir;
// 	while (redirs)
// 	{
// 		if (redirs->type == D_HEREDOC)
// 			ft_process_heredoc(redirs, data);
// 		else
// 			redirs->argv = ft_expand_and_clean(redirs->file, data);
// 		redirs = redirs->next;
// 	}
// }

void	read_pipe(t_ast_node *node, t_data *data, int i)
{
	// if (!node)
	// 	return ;
	// if (node->argv)
	// {
		
				
	// 	multi_pipe(node, data, i);
	// 	// close(data->stdin_backup);
	// 	// close(data->stdout_backup);
	// }
	// if (node->type == NODE_PIPE)
	// {
	// 	read_pipe(node->left, data, i++);
	// 	if (data->isheredoc == false)
	// 		read_pipe(node->right, data, i);
	// }

	(void)node;
	(void)data;
	(void)i;

	t_ast_node *current_left = NULL;
	// t_ast_node *current_right = NULL;
	t_ast_node *current = NULL;

	
	t_ast_node *new_tree = NULL;
	t_ast_node *new_tree_head = NULL;

	current = node;

	int count = 0;

	while(current)
	{
		if (count == 0)
		{
			new_tree = malloc(sizeof(t_ast_node));
			if (!new_tree)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			ft_memcpy(new_tree, current, sizeof(t_ast_node));
			new_tree_head = new_tree;
		}

		current_left = current->left;
		if (current_left && current_left->command != NULL)
		{
			// printf("Left: %s\n", current_left->command);
			new_tree->right = malloc(sizeof(t_ast_node));
			if (!new_tree->right)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			ft_memcpy(new_tree->right, current_left, sizeof(t_ast_node));
			new_tree = new_tree->right;
		}
		if (current && current->command != NULL)
		{
			// printf("Current: %s\n", current->command);
			new_tree->right = malloc(sizeof(t_ast_node));
			if (!new_tree->right)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			ft_memcpy(new_tree->right, current, sizeof(t_ast_node));
			new_tree = new_tree->right;
		}
		current = current->right;
		count++;
	}

	new_tree_head = new_tree_head->right;
	current = new_tree_head;
	while (current)
	{
		if (current->right)
		{
			current->right->prev = malloc(sizeof(t_ast_node));
			if (!current->right->prev)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			ft_memcpy(current->right->prev, current, sizeof(t_ast_node));
		}
		current = current->right;
	}


	current = new_tree_head;

	data->new_ast = new_tree_head;
	while (current)
	{
		printf("Command: %s\n", current->command);
		if (current->prev)
			printf("Command prev: %s\n", current->prev->command);
		current = current->right;
	}


	printf("Count: %d\n", count);
}

void	ft_execution(t_data *data)
{
	if (!data->ast)
		return ;
	count_levels(data->ast, 0, data);
	read_redirs(data->ast, data);
	data->stdin_backup = dup(STDIN_FILENO);
    data->stdout_backup = dup(STDOUT_FILENO);
	if (data->stdin_backup == -1 || data->stdout_backup == -1)
    	ft_error(data, "Error backing up stdin/stdout");
	
	if (data->isheredoc)
		read_heredoc(data->ast, data);
	if (data->isheredoc == false)
		if (data->nb_levels == 0)
			no_pipe(data->ast, data);
	// if (data->nb_levels == 1)
	// 	one_pipe(data->ast, data);
	data->count = 0;
	if (data->nb_levels >= 1)
		read_pipe(data->ast, data, 0);
	
	printf("Count: %d\n", data->count);
	close(data->stdin_backup);
    close(data->stdout_backup);
}
