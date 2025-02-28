/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:16:40 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 16:07:10 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_token_size(char *str)
{
	int	type;
	int	i;

	if (!str)
		return (-1);
	type = get_type(str);
	if (type == -1)
		return (len_invalid_type(str));
	if (type == T_REDIR_APPEND || type == T_REDIR_HERE)
		return (2);
	if (type == T_PIPE || type == T_REDIR_IN || type == T_REDIR_OUT)
		return (1);
	i = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '|' && str[i] != '<'
		&& str[i] != '>')
	{
		if ((str[i] == DQ || str[i] == SQ) && str[i + 1] != '\0')
			i += ft_strchr(&str[i + 1], str[i]) - &str[i] + 1;
		else
			i++;
	}
	return (i);
}

static char	*get_token(char *str)
{
	char	*token_value;
	int		len;

	len = get_token_size(str);
	if (len == -1)
		return (NULL);
	token_value = ft_strndup(str, len);
	if (!token_value)
		return (NULL);
	return (token_value);
}

static t_token	*tokenize(char *str, t_data *data)
{
	int		i;
	char	*substr;
	t_token	*new_token;

	i = 0;
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else
		{
			substr = get_token(str);
			if (!substr)
				return (free_tokens(&data->tokens), NULL);
			new_token = create_token(substr, get_type(substr), 0);
			if (!new_token)
				return (free(substr), free_tokens(&data->tokens), NULL);
			add_token_back(&data->tokens, new_token);
			str += ft_strlen(substr);
			free(substr);
			i++;
		}
	}
	return (data->tokens);
}

int	lexer(t_data *data)
{
	char	*expanded_input;

	if (!data->user_line)
		exit(EXIT_FAILURE);
	else if (ft_strcmp(data->user_line, "\0") == 0)
		return (EXIT_FAILURE);
	else if (check_empty_or_whitespace(data->user_line))
		return (EXIT_SUCCESS);
	add_history(data->user_line);
	if (!valid_quotes(data->user_line))
		return (printf("Error: invalid quotes\n"), EXIT_FAILURE);
	expanded_input = expanding(data->user_line, data);
	if (!expanded_input)
		return (EXIT_SUCCESS);
	data->tokens = tokenize(expanded_input, data);
	free(expanded_input);
	if (!data->tokens)
		return (EXIT_FAILURE);
	set_redirection_types(data->tokens);
	update_token_quote_status(data->tokens);
	remove_quotes(data->tokens);
	if (!check_syntax(data->tokens, data))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
