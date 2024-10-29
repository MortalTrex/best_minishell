#include "minishell.h"

void	ft_free_command(t_ast_node *node)
{
	t_redir	*curr_node;
	t_redir	*next;

	if (!node)
		return ;
	free(node->command);
	node->command = NULL;
	curr_node = node->redir;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->command);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	node->redir = NULL;
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
void free_ast(t_ast_node **node, t_data *data)
{
	free_node(*node);
	*node = NULL;
	if (data->tok)
		ft_stackclear(&data->tok);
}

void ft_free_all(t_data *data)
{
	if (!data)
		return;
	if (data->user_line)
		free(data->user_line);
	if (data->tok)
		ft_stackclear(&data->tok);
	if (data->tmp_token)
		ft_stackclear(&data->tmp_token);
	if (data->env)
		ft_envclear(&data->env);
	if (data->envc)
		ft_free_tab(data->envc);
	if (data->ast)
		free_ast(&(data->ast), data);
}
