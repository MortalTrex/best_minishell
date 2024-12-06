/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 18:51:30 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_errors_in_tokens(t_token *tokens)
{
    t_token *current = tokens;
    while (current)
    {
        if (current->type == T_PIPE && (!current->prev || !current->next || current->prev->type == T_PIPE || current->next->type == T_PIPE))
            return true;
        if (current->type == T_REDIR_IN && (!current->next || current->next->type != T_INFILE))
            return true;
        if (current->type == T_REDIR_OUT && (!current->next || current->next->type != T_OUTFILE))
            return true;
        if (current->type == T_REDIR_APPEND && (!current->next || current->next->type != T_APPENDFILE))
            return true;
        if (current->type == T_REDIR_HERE && (!current->next || current->next->type != T_DELIMITER))
            return true;
        current = current->next;
    }
    return false;
}

bool ft_check_if_quotes_closes(t_data *data) 
{
    if (!data || !data->user_line)
        return false;

    char *line;
    bool single_quote_open;
    bool double_quote_open;

    line = data->user_line;
    single_quote_open = false;
    double_quote_open = false;
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == '\\' && double_quote_open && line[i + 1] != '\0') 
            i++;
        else if (line[i] == '\'' && !double_quote_open)
            single_quote_open = !single_quote_open;
        else if (line[i] == '"' && !single_quote_open)  
            double_quote_open = !double_quote_open;
    }
    if (single_quote_open || double_quote_open) 
        return false;
    return true; 
}
