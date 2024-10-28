 #include "minishell.h"

 void free_cmd(t_cmd *cmd)
{
	printf("\033[1;31mFreeing command\033[0m\n");
	t_redir *redir;
	t_redir *tmp;

	redir = cmd->redir;
	tmp = redir;
	if (cmd->argv)
	{
		ft_free_tab(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->redir)
	{
		while (redir)
		{
			redir = redir->next;
			if (tmp->file)
			{
				free(tmp->file);
				tmp->file = NULL;
			}
			free(tmp);
		}
	}
	free(cmd);
	cmd = NULL;
}

void free_ast(t_ast_node *node)
{
	if (!node)
		return;
	 if (node->left)
    {
        free_ast(node->left);
        node->left = NULL;
    }
    if (node->right)
    {
        free_ast(node->right);
        node->right = NULL;
    }
    if (node->cmd)
    {
        free_cmd(node->cmd);
        node->cmd = NULL;
    }
    if (node->file)
    {
        free(node->file);
        node->file = NULL;
    }
    free(node);
    node = NULL;
}

void	ft_free_all(t_data *data)
{
	if (!data)
		return ;
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
		free_ast(&data->ast);
}
