/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:27:06 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/12/14 13:03:43 by rbalazs          ###   ########.fr       */
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

bool	check_pipe_syntax(t_token *token, t_data *data)
{
	t_token	*current;

	current = token;
	if (current && current->type == T_PIPE)
		return (data->parsing_error = ERR_SYN, false);
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (!current->next)
				return (data->parsing_error = ERR_SYN, false);
			if (current->next && current->next->type == T_PIPE)
				return (data->parsing_error = ERR_SYN, false);
			if (current->next && current->next->type != T_WORD)
				return (data->parsing_error = ERR_SYN, false);
		}
		current = current->next;
	}
	return (true);
}
// change piipe syntax errors

void	ft_parsing_error(t_data *data)
{
	if (data->parsing_error)
	{
		if (data->parsing_error == ERR_SYN)
		{
			ft_putstr_fd("minishell> syntax error near unexpected token\n", 2);
			data->exit_status = 2;
		}
		free_ast(&data->ast, data);
		data->parsing_error = 0;
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	total_length = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = ft_calloc(total_length, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (free(s1), free(s2), joined);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (s[i] && i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
