/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:56:45 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 16:07:45 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_invalid_syntax_error(t_token *token, t_data *data)
{
	size_t	len;

	len = ft_strlen(token->value);
	if (token->value[0] == '>' && token->value[1] == '>' && len >= 4)
		return (handle_token_syntax_error(">>", data));
	if (token->value[0] == '<' && token->value[1] == '<' && len >= 6)
		return (handle_token_syntax_error("<<<", data));
	if (token->value[0] == '<' && token->value[1] == '<' && len >= 4)
		return (handle_token_syntax_error("<<", data));
	if (token->value[0] == '>')
		return (handle_token_syntax_error(">", data));
	if (token->value[0] == '<')
		return (handle_token_syntax_error("<", data));
	if (token->value[0] == '|' && token->value[1] == '|' && len >= 2)
		return (handle_token_syntax_error("||", data));
	if (token->value[0] == '|')
		return (handle_token_syntax_error("|", data));
	return (0);
}

int	validate_heredoc_syntax(t_token *tokens, t_data *data)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == -1)
			return (handle_invalid_syntax_error(tmp, data));
		if (tmp->type == T_PIPE)
		{
			if (!tmp->prev || !tmp->next || tmp->prev->value[0] == '|' || \
				tmp->next->value[0] == '|')
				return (handle_invalid_syntax_error(tmp, data));
		}
		if (tmp->type >= T_REDIR_IN && tmp->type <= T_REDIR_HERE)
		{
			if (!tmp->next)
				return (handle_token_syntax_error("newline", data));
			if (tmp->next->type != T_FILENAME && tmp->next->type != T_DELIMITER)
				return (handle_token_syntax_error(tmp->next->value, data));
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	check_token_syntax(t_token *tmp, t_data *data)
{
	if (tmp->type == -1)
		return (handle_invalid_syntax_error(tmp, data));
	if (tmp->type == T_PIPE)
	{
		if (!tmp->prev || !tmp->next || tmp->prev->type == T_PIPE || \
			tmp->next->type == T_PIPE)
			return (handle_invalid_syntax_error(tmp, data));
	}
	if (tmp->type >= T_REDIR_IN && tmp->type <= T_REDIR_HERE)
	{
		if (!tmp->next)
			return (handle_token_syntax_error("newline", data));
		if (tmp->next->type != T_FILENAME && tmp->next->type != T_DELIMITER)
			return (handle_token_syntax_error(tmp->next->value, data));
	}
	return (0);
}

static int	process_heredocs(t_token *tokens, t_data *data)
{
	t_token	*tmp;
	int		heredoc;
	int		ret;

	tmp = tokens;
	heredoc = 0;
	ret = 0;
	while (tmp && tmp->type != -1)
	{
		if (tmp->type == T_DELIMITER)
		{
			ret = handle_heredoc(tmp, data, heredoc);
			heredoc++;
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	check_syntax(t_token *tokens, t_data *data)
{
	t_token	*tmp;
	int		ret;

	tmp = tokens;
	ret = process_heredocs(tokens, data);
	if (ret != 0)
		return (ret);
	while (tmp)
	{
		ret = check_token_syntax(tmp, data);
		if (ret != 0)
			return (ret);
		tmp = tmp->next;
	}
	return (ret);
}
