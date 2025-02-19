/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:16:40 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/19 15:12:56 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirs(t_token *tokens)
{
    int i;

    i = 0;
	while (tokens)
	{
		if ((tokens->type >= T_REDIR_IN && tokens->type <= T_REDIR_APPEND
			&& (tokens->next && tokens->next->type == T_WORD)))
			tokens->next->type = T_FILENAME;
		else if (tokens->type == T_REDIR_HERE && (tokens->next
				&& tokens->next->type == T_WORD))
			tokens->next->type = T_DELIMITER;
        if (tokens->type == T_DELIMITER)
        {
            while (tokens->value[i])
            {
                if (tokens->value[i] =='\"'|| tokens->value[i] == '\'')
                    tokens->quotes = 1;
                i++;
            }
        }
		tokens = tokens->next;
	}
}
void	remove_quotes(t_token *tokens)
{
	t_token	*temp;
	char	*unquoted_value;

	temp = tokens;
	while (temp)
	{
		if (temp->value)
            ft_remove_quotes(temp->value);
		temp = temp->next;
	}
}

int lexer(t_data *data)
{    char *expand;
    if (!data->user_line)
        exit(EXIT_FAILURE);
    else if (data->user_line[0] == '\0')
        return (EXIT_FAILURE);
    else if (str_is_empty(data->user_line))
        return (EXIT_FAILURE);
    add_history(data->user_line);
    if(check_quotes(data->user_line))
        return (ft_putstr_fd("minishell: syntax error near unexpected token\n", \
            2), EXIT_FAILURE);
    expand = expander(data->user_line, data);
    if (!expand)
        return (EXIT_SUCCESS);
    data->tokens = ft_tokenize(expand, data);
    free(expand);
    if (!data->tokens)
        return (EXIT_FAILURE);
    check_redirs(data->tokens);
    remove_quotes(data->tokens);
    if(!syntax_check(data->tokens, data))
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}