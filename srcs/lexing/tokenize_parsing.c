/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 18:41:48 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *add_spaces_around_tokens(const char *prompt)
{
    const char *tokens[] = { "=", "<<", ">>", "<", ">", "|", NULL };
    
    char *new_prompt = malloc(ft_strlen(prompt) * 2 + 1);
    if (!new_prompt)
        return (NULL);
    char *dest = new_prompt;
    while (*prompt)
    {
        bool matched = false;
        for (int i = 0; tokens[i]; i++)
        {
            size_t token_len = ft_strlen(tokens[i]);
            if (ft_strncmp(prompt, tokens[i], token_len) == 0)
            {
                if (dest != new_prompt && *(dest - 1) != ' ')
                    *dest++ = ' ';
                ft_strncpy(dest, tokens[i], token_len);
                dest += token_len;
                if (*(prompt + token_len) != ' ') 
                    *dest++ = ' ';
                prompt += token_len;
                matched = true;
                break;
            }
        }
        if (!matched)
            *dest++ = *prompt++;
    }
    *dest = '\0'; 
    return (new_prompt);
}


char *replace_spaces_in_quotes(const char *prompt)
{
    char *result = ft_strdup(prompt); 
    if (!result)
        return NULL;

    bool in_single_quotes = false;
    bool in_double_quotes = false;

    for (size_t i = 0; result[i]; i++)
    {
        if (result[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
        }
        else if (result[i] == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;
        }
        else if ((in_single_quotes || in_double_quotes) && result[i] == ' ')
        {
            result[i] = '\x01'; 
        }
    }

    
    if (in_single_quotes || in_double_quotes)
    {
        
        for (size_t i = 0; result[i]; i++)
        {
            if (result[i] == '\x01')
                result[i] = ' ';
        }
    }

    return result;
}
