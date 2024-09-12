/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:58 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/12 17:30:11 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_append_operator(t_data *data, char *line, unsigned int *i)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return;
    new_token->type = T_OPERATOR;
    if (ft_is_multi_char_operator(&line[*i]))
    {
        new_token->value = strndup(&line[*i], 2); // 2 caractères pour les opérateurs multi-caractères
        (*i) += 2;
    }
    else
    {
        new_token->value = strndup(&line[*i], 1); // 1 caractère pour les opérateurs simple caractère
        (*i)++;
    }
    new_token->next = NULL;
    ft_stackadd_back(&data->tok, new_token); // Utiliser data->tok
}

void ft_word_to_token(t_data *data, char *line, unsigned int start, int len)
{
    char    *substr;
    t_token *new_token;

    substr = ft_substr(line, start, len);
    if (!substr)
    {
        fprintf(stderr, "Error: ft_substr returned NULL\n");
        return;
    }
    new_token = ft_stacknew(T_WORD, substr);
    if (!new_token)
    {
        free(substr);
        fprintf(stderr, "Error: ft_stacknew_token returned NULL\n");
        return;
    }
    ft_stackadd_back(&data->tok, new_token); // Utiliser data->tok
}

bool ft_append_word(t_data *data, char *token_buffer)
{
    t_token *new_token;
    char    *word;

    if (!token_buffer || token_buffer[0] == '\0')
        return false;
    word = strdup(token_buffer);
    if (!word)
    {
        fprintf(stderr, "Error: strdup failed to allocate memory\n");
        return false;
    }
    new_token = ft_stacknew(T_WORD, word);
    if (!new_token)
    {
        free(word);
        fprintf(stderr, "Error: ft_stacknew_token returned NULL\n");
        return false;
    }
    ft_stackadd_back(&data->tok, new_token); // Utiliser data->tok
    return true;
}

bool	ft_append_word_quotes(char *token_buffer, int *buffer_index,
		char *line, unsigned int *i)
{
	char	quote; 
	
	quote = line[*i];
	(*i)++;
	while (line[*i] != quote && line[*i] != '\0')
	{
		token_buffer[(*buffer_index)++] = line[(*i)++];
	}
	if (line[*i] == quote)
		(*i)++;
	else
		return (false);
	return (true);
}

void ft_append_env_var(t_data *data, char *line, unsigned int *i)
{
    unsigned int    start;
    unsigned int    len;
    char            *env_var_name;
    t_token         *new_token;

    start = *i;
    len = 1;
    while (line[start + len] && (ft_isalnum(line[start + len]) || line[start + len] == '_'))
        len++;
    env_var_name = ft_substr(line, start, len);
    if (!env_var_name)
    {
        fprintf(stderr, "Error: ft_substr failed to allocate memory\n");
        return ;
    }
    new_token = ft_stacknew(T_ENV_VAR, env_var_name);
    if (!new_token)
    {
        free(env_var_name);
        fprintf(stderr, "Error: ft_stacknew_token failed to allocate memory\n");
        return ;
    }
    ft_stackadd_back(&data->tok, new_token); // Utiliser data->tok
    *i = start + len;
}
