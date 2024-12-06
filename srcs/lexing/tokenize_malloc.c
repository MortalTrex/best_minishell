/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 18:49:37 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tokens(t_token **tokens)
{
    t_token *current = *tokens;
    while (current)
    {
        t_token *temp = current;
        current = current->next;
        free(temp->value);
        free(temp);
    }
    *tokens = NULL;
}

static t_token_type identify_type_of_word(char *word)
{
    if (ft_strcmp(word, "|") == 0)
        return (T_PIPE);

    else if (ft_strcmp(word, "<") == 0)
        return (T_REDIR_IN);
    else if (ft_strcmp(word, ">") == 0)
        return (T_REDIR_OUT);
    else if (ft_strcmp(word, ">>") == 0)
        return (T_REDIR_APPEND);
    else if (ft_strcmp(word, "<<") == 0)
        return (T_REDIR_HERE);
    return (T_ARG);
}

t_token *fill_list_tokens(char *prompt)
{
    t_token *tokens = NULL;
    t_token *last_token = NULL;

    char **words = ft_split(prompt, ' ');
    if (!words)
        return (NULL);

    for (int i = 0; words[i]; i++)
    {
        t_token_type type = identify_type_of_word(words[i]);
        t_token *new_token = ft_create_new_token(words[i], type);

        if (!new_token)
        {
            for (int j = 0; words[j]; j++)
                free(words[j]);
            free(words);
            while (tokens)
            {
                t_token *temp = tokens;
                tokens = tokens->next;
                free(temp->value);
                free(temp);
            }
            return (NULL);
        }
        if (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_REDIR_APPEND || type == T_REDIR_HERE)
        {
            if (words[i + 1])
            {
                i++;
                t_token_type subtype = T_ARG;
                if (type == T_REDIR_IN)
                    subtype = T_INFILE;
                else if (type == T_REDIR_OUT)
                    subtype = T_OUTFILE;
                else if (type == T_REDIR_APPEND)
                    subtype = T_APPENDFILE;
                else if (type == T_REDIR_HERE)
                    subtype = T_DELIMITER;

                t_token *extra_token = ft_create_new_token(words[i], subtype);
                if (!extra_token)
                {
                    free(new_token->value);
                    free(new_token);
                    for (int j = 0; words[j]; j++)
                        free(words[j]);
                    free(words);
                    while (tokens)
                    {
                        t_token *temp = tokens;
                        tokens = tokens->next;
                        free(temp->value);
                        free(temp);
                    }
                    return (NULL);
                }
                new_token->next = extra_token;
                extra_token->prev = new_token;

                if (!tokens)
                    tokens = new_token;
                else
                {
                    last_token->next = new_token;
                    new_token->prev = last_token;
                }
                last_token = extra_token;
                continue;
            }
        }
        if (!tokens)
            tokens = new_token;
        else
        {
            last_token->next = new_token;
            new_token->prev = last_token;
        }
        last_token = new_token;
    }    
    t_token *current = tokens;
    bool pipe = false;
    while (current)
    {
        if (current->type == T_ARG && !pipe)
        {
            current->type = T_CMD;
            pipe = true;
        }
        if (current->type == T_PIPE)
            pipe = false;
        current = current->next;
    }
    for (int i = 0; words[i]; i++)
        free(words[i]);
    free(words);
    return (tokens);
}

