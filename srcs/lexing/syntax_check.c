/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:56:45 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 18:39:41 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_invalid_syntax_error(t_token *token, t_data *shell)
{
	if (token->value[0] == '>' && token->value[1] == '>'
		&& ft_strlen(token->value) >= 4)
		return (handle_token_syntax_error(">>", shell));
	else if (token->value[0] == '<' && token->value[1] == '<'
		&& ft_strlen(token->value) >= 6)
		return (handle_token_syntax_error("<<<", shell));
	else if (token->value[0] == '<' && token->value[1] == '<'
		&& ft_strlen(token->value) >= 4)
		return (handle_token_syntax_error("<<", shell));
	else if (token->value[0] == '>')
		return (handle_token_syntax_error(">", shell));
	else if (token->value[0] == '<')
		return (handle_token_syntax_error("<", shell));
	else if (token->value[0] == '|' && token->value[1] == '|'
		&& ft_strlen(token->value) >= 2)
		return (handle_token_syntax_error("||", shell));
	if (token->value[0] == '|')
		return (handle_token_syntax_error("|", shell));
	return (0);
}

int	validate_heredoc_syntax(t_token *tokens, t_data *shell)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == -1)
			return (handle_invalid_syntax_error(tmp, shell));
		else if (tmp->type == T_PIPE && (!tmp->prev || !tmp->next
				|| tmp->prev->value[0] == '|' || tmp->next->value[0] == '|'))
			return (handle_invalid_syntax_error(tmp, shell));
		else if (tmp->type >= T_REDIR_IN && tmp->type <= T_REDIR_HERE)
		{
			if (!tmp->next)
				return (handle_token_syntax_error("newline", shell));
			else if (tmp->next->type != T_FILENAME
				&& tmp->next->type != T_DELIMITER)
				return (handle_token_syntax_error(tmp->next->value, shell));
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	no_heredoc_syntax(t_token *tmp, t_data *shell)
{
	if (tmp->type == -1)
		return (handle_invalid_syntax_error(tmp, shell));
	else if (tmp->type == T_PIPE && (!tmp->prev || !tmp->next
			|| tmp->prev->type == T_PIPE || tmp->next->type == T_PIPE))
		return (handle_invalid_syntax_error(tmp, shell));
	else if (tmp->type >= T_REDIR_IN && tmp->type <= T_REDIR_HERE)
	{
		if (!tmp->next)
			return (handle_token_syntax_error("newline", shell));
		else if (tmp->next->type != T_FILENAME
			&& tmp->next->type != T_DELIMITER)
			return (handle_token_syntax_error(tmp->next->value, shell));
	}
	return (0);
}

static int	process_heredocs(t_token *tokens, t_data *shell)
{
	t_token	*tmp;
	int		heredoc;
	int		ret;

	heredoc = 0;
	tmp = tokens;
	ret = 0;
	while (tmp && tmp->type != -1)
	{
		if (tmp->type == T_DELIMITER)
		{
			if (heredoc == 0)
				ret = handle_heredoc(tmp, shell, heredoc);
			else
				handle_heredoc(tmp, shell, heredoc);
			heredoc++;
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	check_syntax(t_token *tokens, t_data *shell)
{
	t_token	*tmp;
	int		ret;

	tmp = tokens;
	ret = 0;
	ret = process_heredocs(tokens, shell);
	if (ret != 0)
		return (ret);
	while (tmp)
	{
		ret = no_heredoc_syntax(tmp, shell);
		if (ret != 0)
			return (ret);
		tmp = tmp->next;
	}
	return (ret);
}
