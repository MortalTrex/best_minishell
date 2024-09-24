/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/24 15:11:42 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_detect_builtin(t_data *data)
{
	t_token	*current;

	current = data->tok;
	while (current)
	{
		if (current->type == T_WORD)
		{
			if (!ft_strcmp(current->value, "cd"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "echo"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "pwd"))
			{
				current->type = T_BUILTIN;
				ft_pwd();
			}
			else if (!ft_strcmp(current->value, "export"))
			{
				current->type = T_BUILTIN;
				ft_export(data);
			}
			else if (!ft_strcmp(current->value, "unset"))
			{
				current->type = T_BUILTIN;
				ft_unset(data);
			}
			else if (!ft_strcmp(current->value, "env"))
			{
				current->type = T_BUILTIN;
				ft_env(data);
			}
			else if (!ft_strcmp(current->value, "exit"))
			ft_exit(data);
		}
		current = current->next;
	}
}

bool	ft_finalize_tokenization(t_data *data, char *token_buffer, int buffer_index, bool is_quotes)
{
	if (buffer_index > 0)
	{
		token_buffer[buffer_index] = '\0';
		ft_append_word(data, token_buffer);
	}
	if (is_quotes == false)
		return (ft_msg_free_exit("Error: Unclosed quotes\n", data), false);
	ft_detect_builtin(data);
	ft_stackadd_back(&data->tok, ft_stacknew(T_EOF, NULL));
	return (true);
}

bool	ft_process_operator(t_data *data, unsigned int *i, char *token_buffer, int *buffer_index)
{
	if (*buffer_index > 0)
	{
		token_buffer[*buffer_index] = '\0';
		ft_append_word(data, token_buffer);
		*buffer_index = 0;
	}
	ft_append_operator(data, data->user_line, i);
	if (data->user_line[*i] != '\0' && ft_is_operator(data->user_line[*i]))
	{
		fprintf(stderr, "Error: Unexpected operator sequence\n");
		return (false);
	}
	return (true);
}


bool	ft_process_whitespace(t_data *data, unsigned int *i, char *token_buffer, int *buffer_index)
{
	if (ft_isspace(data->user_line[*i]))
	{
		if (*buffer_index > 0)
		{
			token_buffer[*buffer_index] = '\0';
			ft_append_word(data, token_buffer);
			*buffer_index = 0;
		}
		(*i)++;
		return (true);
	}
	return (true);
}


bool	ft_tokenize(t_data *data)
{
	unsigned int	i;
	bool			is_quotes;
	char			token_buffer[256];
	int				buffer_index;

	i = 0;
	is_quotes = true;
	buffer_index = 0;
	while (data->user_line[i] != '\0')
	{
		if (!ft_process_whitespace(data, &i, token_buffer, &buffer_index))
			return (false);
		else if (ft_is_quote(data->user_line[i]))
			is_quotes = ft_append_word_quotes(token_buffer, &buffer_index, data->user_line, &i);
		else if (data->user_line[i] == '$')
			ft_append_env_var(data, data->user_line, &i);
		else if (ft_is_operator(data->user_line[i]))
		{
			if (!ft_process_operator(data, &i, token_buffer, &buffer_index))
				return (false);
		}
		else
		{
			token_buffer[buffer_index++] = data->user_line[i++];
		}
	}
	return (ft_finalize_tokenization(data, token_buffer, buffer_index, is_quotes));
}


/* bool	ft_tokenize(t_data *data)
{
	unsigned int	i;
	bool			is_quotes;
	char			token_buffer[256];
	int				buffer_index;

	i = 0;
	is_quotes = true;
	buffer_index = 0;
	while (data->user_line[i] != '\0')
	{
		if (ft_isspace(data->user_line[i]))
		{
			if (buffer_index > 0)
			{
				token_buffer[buffer_index] = '\0';
				ft_append_word(data, token_buffer);
				buffer_index = 0;
			}
			i++;
		}
		else if (data->user_line[i] == '"' || data->user_line[i] == '\'')
			is_quotes = ft_append_word_quotes(token_buffer, &buffer_index,
					data->user_line, &i);
		else if (data->user_line[i] == '$')
			ft_append_env_var(data, data->user_line, &i);
		else if (ft_is_operator(data->user_line[i]))
		{
			if (buffer_index > 0)
			{
				token_buffer[buffer_index] = '\0';
				ft_append_word(data, token_buffer);
				buffer_index = 0;
			}
			ft_append_operator(data, data->user_line, &i);
			if (data->user_line[i] != '\0'&& ft_is_operator(data->user_line[i]))
				return (fprintf(stderr,
						"Error: Unexpected operator sequence\n"), false);
		}
		else
			token_buffer[buffer_index++] = data->user_line[i++];
	}
	if (buffer_index > 0)
	{
		token_buffer[buffer_index] = '\0';
		ft_append_word(data, token_buffer);
	}
	if (is_quotes == false)
		return (ft_error(data, "Error: Unclosed quotes\n"), false);
	ft_detect_builtin(data);
	return (ft_stackadd_back(&data->tok, ft_stacknew(T_EOF, NULL)), true);
} */
