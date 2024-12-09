/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/09 13:20:50 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_check_redirs(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == T_PIPE && (!current->prev || !current->next
				|| current->prev->type == T_PIPE
				|| current->next->type == T_PIPE))
			return (true);
		if (current->type == T_REDIR_IN && (!current->next
				|| current->next->type != T_INFILE))
			return (true);
		if (current->type == T_REDIR_OUT && (!current->next
				|| current->next->type != T_OUTFILE))
			return (true);
		if (current->type == T_REDIR_APPEND && (!current->next
				|| current->next->type != T_APPENDFILE))
			return (true);
		if (current->type == T_REDIR_HERE && (!current->next
				|| current->next->type != T_DELIMITER))
			return (true);
		current = current->next;
	}
	return (false);
}

static bool	ft_check_if_cmd_exist(t_token *tokens)
{
	t_token	*current;
    
	current = tokens;
	while (current)
	{
		if (current->type == T_CMD)
			return (true);
		current = current->next;
	}
	return (false);	
}

bool	ft_check_errors_in_tokens(t_token *tokens)
{
	printf("check redirs %d\n", ft_check_redirs(tokens));
	printf("check cmd %d\n", ft_check_if_cmd_exist(tokens));
	if (ft_check_redirs(tokens))
		return (true);
	if (!ft_check_if_cmd_exist(tokens))
		return (true);
	return (false);
}

bool	ft_check_if_quotes_closes(t_data *data)
{
	char	*line;
	bool	single_quote_open;
	bool	double_quote_open;
	int		i;

	if (!data || !data->user_line)
		return (false);
	line = data->user_line;
	single_quote_open = false;
	double_quote_open = false;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\\' && double_quote_open && line[i + 1] != '\0')
			i++;
		else if (line[i] == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (line[i] == '"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		i++;
	}
	if (single_quote_open || double_quote_open)
		return (false);
	return (true);
}
