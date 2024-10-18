/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/18 17:47:33 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	ft_op_type(char *op)
{
	if (!ft_strcmp(op, "|"))
		return (T_PIPE);
	else if (!ft_strcmp(op, ">"))
		return (T_REDIR_OUT);
	else if (!ft_strcmp(op, ">>"))
		return (T_REDIR_APPEND);
	else if (!ft_strcmp(op, "<"))
		return (T_REDIR_IN);
	else if (!ft_strcmp(op, "<<"))
		return (T_REDIR_HERE);
	return (T_OPERATOR);
}

bool	ft_append_operator(char **command, t_token **tokens)
{
	t_token	*new_token;

	if (ft_is_multi_char_operator(*command))
	{
		new_token = ft_stacknew(T_OPERATOR, NULL);
		if (ft_strchr(*command, '<'))
			new_token->value = ft_strdup("<<");
		else
			new_token->value = ft_strdup(">>");
		new_token->type = ft_op_type(new_token->value);
		(*command) += 2;
	}
	else
	{
		new_token = ft_stacknew(T_OPERATOR, NULL);
		new_token->value = strndup(*command, 1);
		new_token->type = ft_op_type(new_token->value);
		(*command)++;
	}
	if (!new_token)
		return (false);
	return (ft_stackadd_back(tokens, new_token), true);
}

bool	ft_append_word(char **command, t_token **tokens)
{
	char	*line;
	char 	*value;
	size_t		i;
	t_token	*new_token;

	line = *command;
	i = 0;
	while (!ft_is_separator(line + i) && line[i])
	{
		if (ft_is_quote(line[i]))
		{
			if (!ft_skip_quotes(line, &i))
				return (false);
		}
		else
			i++;
	}
	value = ft_substr(line, 0, i);
	if (!value)
		return (false);
	new_token = ft_stacknew(T_WORD, value);
	if (!new_token)
		return (free(value), false);
	*command += i;
	return (ft_stackadd_back(tokens, new_token), true);
}
