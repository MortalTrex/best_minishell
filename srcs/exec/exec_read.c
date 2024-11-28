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

void    read_commands(t_ast_node *node, t_data *data)
{
	t_ast_node *current;

	current = node;
	(void)data;
	while (current)
	{
		//printf("Command: %s\n", current->command);
		if (current->prev)
			printf("Command: %s\n", current->prev->command);
		current = current->right;
	}
}

void	transform_ast(t_ast_node *node, t_data *data)
{
	(void)node;
	(void)data;
	int i;
	int count;

	t_ast_node *current_left;
	t_ast_node *current;
	t_ast_node *new_tree;
	t_ast_node *new_tree_head;

	current_left = NULL;
	current = node;
	new_tree = NULL;
	new_tree_head = NULL;
	count = 0;
	i = 0;
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
	// while (current)
	// {
	// 	printf("Command: %s\n", current->command);
	// 	if (current->prev)
	// 		printf("Command: %s\n", current->prev->command);
	// 	current = current->right;
	// }
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
	if (data->isheredoc == true)
		ft_process_heredoc(data->ast->redir, data);
	if (data->isheredoc == false)
		if (data->nb_levels == 0)
			no_pipe(data->ast, data);
	transform_ast(data->ast, data);
	data->count = 0;
	if (data->nb_levels >= 1)
		read_commands(data->new_ast, data);
	close(data->stdin_backup);
    close(data->stdout_backup);
}
