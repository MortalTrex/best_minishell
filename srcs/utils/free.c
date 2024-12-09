#include "minishell.h"

static	void	free_redir(t_redir **redir)
{
	t_redir	*next;
	t_redir	*tmp;

	if (!redir)
		return ;
	tmp = *redir;
	while (tmp)
	{
		free(tmp->value);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*redir = NULL;
}

void	ft_free_command(t_ast_node *node)
{
	if (!node)
		return ;
	free_redir(&node->redir);
	free(node->command);
	ft_free_tab(node->argv);
}

void	free_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node -> type == NODE_CMD)
		ft_free_command(node);
	else
	{
		if (node->left)
			free_node(node->left);
		if (node->right)
			free_node(node->right);
	}
	free(node);
}

void	free_ast(t_ast_node **node, t_data *data)
{
	free_node(*node);
	*node = NULL;
	if (data->tok)
		ft_stackclear(&data->tok);
}

// void	ft_free_all_redirs(t_shell_list *shell_list)
// {
// 	t_shell_list	*current;

// 	current = shell_list;
// 	while (current)
// 	{
// 		ft_free_redir_list(current->redir);
// 		current->redir = NULL;
// 		current = current->next;
// 	}
// }

void	ft_free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->user_line)
	{
		free(data->user_line);
		data->user_line = NULL;
	}
	if (data->tok)
	{
		ft_stackclear(&data->tok);
		data->tok = NULL;
	}
	if (data->envc)
	{
		ft_free_tab(data->envc);
		data->envc = NULL;
	}
	if (data->free_value == 0)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		if (data->env)
		{
			ft_envclear(&data->env);
			data->env = NULL;
		}
	}
	if (data->ast)
	{
		free_ast(&data->ast, data);
		data->ast = NULL;
	}
	if (data->shell_list)
	{
		ft_free_shell_list(data->shell_list);
		data->shell_list = NULL;
	}
}