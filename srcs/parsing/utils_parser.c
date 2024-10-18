/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:27:06 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/18 18:59:50 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (node->cmd)
		free_cmd(node->cmd);
	if (node->file)
	{
		free(node->file);
		node->file = NULL;
	}
	free(node);
	node = NULL;
}


bool	is_redirection(t_token *token)
{
	if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT \
			||token->type == T_REDIR_HERE || token->type == T_REDIR_APPEND)
		return (true);
	return (false);
}

bool check_pipe_syntax(t_token *token)
{
	t_token *current = token;

	if (current && current->type == T_PIPE)
		return (fprintf(stderr, "Syntax error: unexpected pipe at the beginning\n"), false);
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (!current->next)
				return (fprintf(stderr, "Syntax error: unexpected pipe at the end\n"), false);
			if (current->next && current->next->type == T_PIPE)
				return (fprintf(stderr, "Syntax error: consecutive pipes\n"), false);
			if (current->next && current->next->type != T_WORD && current->next->type != T_BUILTIN)
				return (fprintf(stderr, "Syntax error: pipe not followed by a command\n"), false);
		}
		current = current->next;
	}
	return (true);
}

void ft_expand_env_vars(t_token **tokens)
{
	t_token *current = *tokens;

	while (current)
	{
		if (current->type == T_WORD && current->value[0] == '$')
		{
			char *env_value = getenv(current->value + 1); // Skip the '$'
			if (env_value)
			{
				printf("Expanding %s to %s\n", current->value, env_value);
				free(current->value);				// Free old value
				current->value = strdup(env_value); // Replace with expanded value
			}
			else
			{
				printf("Environment variable %s not found.\n", current->value);
				current->value = strdup(""); // Set to an empty string
			}
			current->type = T_WORD;
		}
		current = current->next;
	}
}
