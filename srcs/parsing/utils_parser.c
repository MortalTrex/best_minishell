/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:27:06 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/28 17:55:41 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_expand_env_vars(t_token **tokens)
{
	t_token	*current;
	char	*env_value;
	int i;

	current = *tokens;
	while (current)
	{
		if (current->type == T_WORD && current->value[0] == '$')
		{
			if (env_value)
			{
				free(current->value);
				current->value = strdup(env_value);
			}
			else
				current->value = strdup("");
		}
		current = current->next;
	}
}

void ft_parsing_error(t_data *data)
{
	if (data->error_msg)
	{
		if (ft_strcmp(data->error_msg, ERR_SYN))
		{
			ft_putstr_fd("minishell> \n", 2);
			ft_putstr_fd(data->error_msg, 2);
			data->exit_status = 258;
		}
		free_ast(data->ast);
		free(data->error_msg);
	}
}
