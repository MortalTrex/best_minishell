/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:37 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 18:45:29 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	check_if_other_heredoc(t_token *current)
{
	t_token	*tmp;

	tmp = current->next;
	while (tmp)
	{
		if (tmp->type == T_REDIR_HERE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	save_heredoc_line(int fd, char *tmp, t_data *data,
		int quotes_status)
{
	if (quotes_status == 0)
		tmp = expanding(tmp, data);
	if (tmp)
		write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
	if (tmp)
		free(tmp);
}

void	pipe_and_fork(t_cmd *current, t_data *data)
{
	if (current->next)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	data->prev_pid = fork();
	if (data->prev_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	wait_commands(t_data *data)
{
	signal(SIGINT, SIG_IGN);
	while (errno != ECHILD)
	{
		if (wait(&data->wstatus) == data->prev_pid)
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

// static void	free_line(char *line, t_token *tmp)
// {
// 	free(line);
// 	if (tmp->value != line)
// 	{
// 		free(tmp->value);
// 		tmp->value = NULL;
// 	}
// }
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

// void	transform_ast(t_ast_node *node, t_data *data)
// {
// 	t_ast_node *current = node;
// 	t_ast_node *new_tree = NULL;
// 	t_ast_node **new_tree_ptr = &new_tree;

// 	while (current)
// 	{
// 		if (current->left && current->left->command)
// 		{
// 			*new_tree_ptr = malloc(sizeof(t_ast_node));
// 			if (!*new_tree_ptr)
// 			{
// 				perror("malloc");
// 				exit(EXIT_FAILURE);
// 			}
// 			ft_memcpy(*new_tree_ptr, current->left, sizeof(t_ast_node));
// 			new_tree_ptr = &(*new_tree_ptr)->right;
// 		}

// 		if (current->command)
// 		{
// 			*new_tree_ptr = malloc(sizeof(t_ast_node));
// 			if (!*new_tree_ptr)
// 			{
// 				perror("malloc");
// 				exit(EXIT_FAILURE);
// 			}
// 			ft_memcpy(*new_tree_ptr, current, sizeof(t_ast_node));
// 			new_tree_ptr = &(*new_tree_ptr)->right;
// 		}

// 		current = current->right;
// 	}

// 	data->new_ast = new_tree;
// }