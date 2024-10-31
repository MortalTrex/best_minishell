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
		free(tmp->command);
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

void	ft_free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->user_line)
		free(data->user_line);
	if (data->tok)
		ft_stackclear(&data->tok);
	if (data->envc)
		ft_free_tab(data->envc);
	if (data->free_value == 0)
	{
		if (data->env)
			ft_envclear(&data->env);
	}
	if (data->ast)
		free_ast(&data->ast, data);
}