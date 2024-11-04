/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/04 15:02:17 by rbalazs          ###   ########.fr       */
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
	return (T_WORD);
}

bool	ft_append_operator(char **command, t_token **tokens)
{
	t_token	*new_token;

	if (ft_is_multi_char_operator(*command))
	{
		new_token = ft_stacknew(T_WORD, NULL);
		if (ft_strchr(*command, '<'))
			new_token->value = ft_strdup("<<");
		else
			new_token->value = ft_strdup(">>");
		new_token->type = ft_op_type(new_token->value);
		(*command) += 2;
	}
	else
	{
		new_token = ft_stacknew(T_WORD, NULL);
		new_token->value = ft_substr(*command, 0, 1);
		new_token->type = ft_op_type(new_token->value);
		(*command)++;
	}
	if (!new_token)
		return (false);
	return (ft_stackadd_back(tokens, new_token), true);
}

char	*ft_waiting_for_quote(char *line, t_data *data)
{
	char	*new_line;
	size_t	j;

	printf("line: %s\n", data->user_line);
	while (true)
	{
		j = 0;
		new_line = readline("> ");
		if (!new_line)
			return (NULL);
		line = ft_strjoin(line, new_line);
		while (new_line[j])
			j++;
		if (new_line[j - 1] == '\'' || new_line[j - 1] == '"')
		{
			free(new_line);
			return (line);
		}
		free(new_line);
	}
	return (line);
}

bool	ft_append_word(char **command, t_token **tokens, t_data *data)
{
    char	*line;
    char	*value;
    size_t	i;
    t_token	*new_token;
    line = *command;
    i = 0;
    while (!ft_is_separator(line + i) && line[i])
    {
        if (ft_is_quote(line[i]))
        {
            if (!ft_skip_quotes(line, &i))
            {
                line = ft_waiting_for_quote(line, data);
                if (!line)
                    return (false);
                i = 0;
            }
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
