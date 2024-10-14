/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/14 17:42:27 by rbalazs          ###   ########.fr       */
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

void	ft_append_operator(t_data *data, char *line, unsigned int *i)
{
	t_token	*new_token;

	if (ft_is_multi_char_operator(&line[*i]))
	{
		new_token = ft_stacknew(T_OPERATOR, NULL);
		new_token->value = strndup(&line[*i], 2);
		new_token->type = ft_op_type(new_token->value);
		(*i) += 2;
	}
	else
	{
		new_token = ft_stacknew(T_OPERATOR, NULL);
		new_token->value = strndup(&line[*i], 1);
		new_token->type = ft_op_type(new_token->value);
		(*i)++;
	}
	if (!new_token)
		return ;
	ft_stackadd_back(&data->tok, new_token);
}

bool	ft_append_word(t_data *data, char *token_buffer, int *buffer_index)
{
	char	*word;
	t_token	*new_token;

	word = ft_substr(token_buffer, 0, *buffer_index);
	if (!word)
		ft_error(data, "Error: ft_substr failed to allocate memory\n");
	new_token = ft_stacknew(T_WORD, word);
	if (!new_token)
	{
		free(word);
		ft_error(data, "Error: ft_stacknew failed to allocate memory\n");
	}
	ft_stackadd_back(&data->tok, new_token);
	return (true);
}

bool	ft_append_word_quotes(char *token_buffer, int *buffer_index, char *line,
		unsigned int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] != quote && line[*i] != '\0')
		token_buffer[(*buffer_index)++] = line[(*i)++];
	if (line[*i] == quote)
		(*i)++;
	else
		return (false);
	return (true);
}

bool	ft_append_env_var(t_data *data, char *line, unsigned int *i)
{
	unsigned int	start;
	unsigned int	len;
	char			*env_var_name;
	t_token			*new_token;

	start = *i;
	len = 1;
	while (line[start + len] && (ft_isalnum(line[start + len]) || line[start
			+ len] == '_'))
		len++;
	env_var_name = ft_substr(line, start, len);
	if (!env_var_name)
		return (ft_error(data, "Error: ft_substr failed to allocate memory\n"),
			false);
	new_token = ft_stacknew(T_ENV_VAR, env_var_name);
	free(env_var_name);
	if (!new_token)
		return (ft_error(data,
				"Error: ft_stacknew failed to allocate memory\n"), false);
	ft_stackadd_back(&data->tok, new_token);
	*i = start + len;
	return (true);
}
