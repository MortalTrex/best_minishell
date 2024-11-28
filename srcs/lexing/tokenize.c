/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/28 18:47:18 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token	*fill_list_tokens(char *command, t_data *data)
// {
// 	t_token	*tokens;
// 	bool	ok;

// 	ok = true;
// 	tokens = NULL;
// 	while (*command)
// 	{
// 		if (ok == false)
// 			return (ft_stackclear(&tokens), NULL);
// 		while (ft_isspace(*command) && *command)
// 			command++;
// 		if (ft_is_operator(*command))
// 			ok = ft_append_operator(&command, &tokens);
// 		else
// 			ok = ft_append_word(&command, &tokens, data);
// 	}
// 	return (tokens);
// }

t_token_type identify_type_of_word(char *word)
{
    if (ft_strcmp(word, "|") == 0)
        return (T_PIPE);
    // else if (ft_strcmp(word, "=") == 0)
    //     return (T_ASSIGN);
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



t_token *fill_list_tokens(char *prompt, t_data *data)
{
    (void)data;
    t_token *tokens = NULL;
    t_token *last_token = NULL;

    prompt = replace_spaces_in_quotes(prompt);

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

        
        // if (type == T_ASSIGN)
        // {
            
        //     if (i > 0)
        //     {
        //         last_token->type = T_VARIABLE; 
        //     }

            
        //     if (words[i + 1])
        //     {
        //         i++;
        //         t_token *extra_token = ft_create_new_token(words[i], T_VALUE_VAR);
        //         if (!extra_token)
        //         {
        //             free(new_token->value);
        //             free(new_token);
        //             for (int j = 0; words[j]; j++)
        //                 free(words[j]);
        //             free(words);
        //             while (tokens)
        //             {
        //                 t_token *temp = tokens;
        //                 tokens = tokens->next;
        //                 free(temp->value);
        //                 free(temp);
        //             }
        //             return (NULL);
        //         }

        //         new_token->next = extra_token;
        //         extra_token->prev = new_token;

        //         if (!tokens)
        //             tokens = new_token;
        //         else
        //         {
        //             last_token->next = new_token;
        //             new_token->prev = last_token;
        //         }
        //         last_token = extra_token;
        //         continue;
        //     }
        // }

        
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



void remove_all_quotes(char **str)
{
	char *src = *str;
	char *dst = *str;

	while (*src)
	{
		if (*src != '\'' && *src != '\"')
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
}

char *choose_type(t_token_type type)
{
	if (type == T_CMD)
		return "T_CMD";
	else if (type == T_ARG)
		return "T_ARG";
	else if (type == T_PIPE)
		return "T_PIPE";
	else if (type == T_ASSIGN)
		return "T_ASSIGN";
	else if (type == T_VARIABLE)
		return "T_VARIABLE";
    else if (type == T_VALUE_VAR)
        return "T_VALUE_VAR";
	else if (type == T_REDIR_IN)
		return "T_REDIR_IN";
	else if (type == T_INFILE)
		return "T_INFILE";
	else if (type == T_REDIR_OUT)
		return "T_REDIR_OUT";
	else if (type == T_OUTFILE)
		return "T_OUTFILE";
	else if (type == T_REDIR_APPEND)
		return "T_REDIR_APPEND";
	else if (type == T_APPENDFILE)
		return "T_APPENDFILE";
	else if (type == T_REDIR_HERE)
		return "T_REDIR_HERE";
	else if (type == T_DELIMITER)
		return "T_DELIMITER";
	else
		return "UNKNOWN";
}

void print_tokens(t_token *tokens)
{
	t_token *current = tokens;
	while (current)
	{
		printf("value: %s - ", current->value);
		char *type_str = choose_type(current->type);
		printf("type: %s - ", type_str);
        if (current->to_expand)
            printf("to_expand: true\n");
        else
            printf("to_expand: false\n");
		current = current->next;
	}
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    for (; i < n; i++)
    {
        dest[i] = '\0';
    }
    return dest;
}


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

bool	ft_found_token_in_argv(t_data *data)
{
	char *prompt;

	prompt = ft_strdup(data->user_line);
	// remove_all_quotes(&prompt);

	prompt = add_spaces_around_tokens(prompt);

	printf("Prompt: %s\n", prompt);

	data->tok = fill_list_tokens(prompt, data);
	
	
	// print_tokens(data->tok);
	
	if (!data->tok)
	{
		free(prompt);
		return (false);
	}

	free(prompt);
	return (true);
}
