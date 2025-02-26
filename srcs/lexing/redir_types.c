/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 15:08:51 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redir_type(char *str, int i, int count, char ch)
{
	int	result_double;
	int	result_single;

	result_double = -1;
	result_single = -1;
	if (ch == '>')
	{
		result_double = T_REDIR_APPEND;
		result_single = T_REDIR_OUT;
	}
	else if (ch == '<')
	{
		result_double = T_REDIR_HERE;
		result_single = T_REDIR_IN;
	}
	count = i;
	while (str[count] == ch)
		count++;
	if (count - i == 2)
		return (result_double);
	else if (count - i == 1)
		return (result_single);
	return (-1);
}

int	check_pipe_type(char *str, int i, int count)
{
	count = i;
	while (str[count] == '|')
		count++;
	if (count - i != 1)
		return (-1);
	return (T_PIPE);
}

int	get_type(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (check_pipe_type(str, i, count));
		else if (str[i] == '>')
			return (check_redir_type(str, i, count, '>'));
		else if (str[i] == '<')
			return (check_redir_type(str, i, count, '<'));
		else
			return (T_WORD);
		i++;
	}
	return (-1);
}

void	set_redirection_types(t_token *tokens)
{
	while (tokens)
	{
		if ((tokens->type >= T_REDIR_IN && tokens->type <= T_REDIR_APPEND)
			&& (tokens->next && tokens->next->type == T_WORD))
			tokens->next->type = T_FILENAME;
		else if (tokens->type == T_REDIR_HERE && (tokens->next
				&& tokens->next->type == T_WORD))
			tokens->next->type = T_DELIMITER;
		tokens = tokens->next;
	}
}
