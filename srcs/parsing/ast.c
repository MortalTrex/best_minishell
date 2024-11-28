/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/28 20:16:48 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_ast_node	*create_tree(t_token **current_token, t_data *data)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*current;

	current = *current_token;
	if (!current)
		return (NULL);
	left = simple_command(&current, data);
	if (!left)
		return (NULL);
	while (current && current->type == T_PIPE)
	{
		current = current->next;
		if (!current || current->type != T_WORD)
			return (data->parsing_error = ERR_SYN, left);
		right = create_tree(&current, data);
		if (!right)
			return (left);
		left = ft_create_pipe_node(data, left, right);
		if (!left)
			return (free_ast(&left, data), free_ast(&right, data), NULL);
	}
	return (left);
}


bool has_single_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'')
			return true;
		str++;
	}
	return false;
}


bool has_double_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '"')
			return true;
		str++;
	}
	return false;
}

bool requires_expansion(const char *str)
{
	bool in_single_quotes = false;
	bool in_double_quotes = false;

	while (*str)
	{
		if (*str == '\'' && !in_double_quotes)
		{
			
			in_single_quotes = !in_single_quotes;
		}
		else if (*str == '"' && !in_single_quotes)
		{
			
			in_double_quotes = !in_double_quotes;
		}
		else if (!in_single_quotes && (*str == '$' || *str == '`' || *str == '\\'))
		{
			
			return true;
		}
		str++;
	}

	
	return false;
}


bool type_not_to_expand(t_token_type type)
{
	if (type == T_PIPE || type == T_ASSIGN || type == T_REDIR_IN || type == T_REDIR_OUT || type == T_REDIR_APPEND || type == T_REDIR_HERE)
		return true;
	return false;
}


void check_if_expand_values(t_data *data)
{
	t_token *current = data->tok;

	while (current)
	{
		
		current->to_expand = false;

		
		if (type_not_to_expand(current->type))
		{
			current = current->next;
			continue;
		}

		
		current->to_expand = requires_expansion(current->value);

		
		current = current->next;
	}
}


char *get_env_value(const char *name, t_env *env)
{
	while (env)
	{
		if (strcmp(env->name, name) == 0)
			return env->value;
		env = env->next;
	}
	return NULL; 
}



char *replace_variable(const char *str, t_env *env)
{
	size_t len = ft_strlen(str);
	char *result = malloc(len + 1); 
	char *res_ptr = result;

	if (!result)
		return NULL; 

	const char *ptr = str;

	while (*ptr)
	{
		if (*ptr == '$') 
		{
			ptr++; 
			const char *start = ptr;

			
			while (*ptr && ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') || (*ptr == '_') || (*ptr >= '0' && *ptr <= '9')))
				ptr++;

			
			size_t var_len = ptr - start;
			char *var_name = ft_strndup(start, var_len);

			
			char *var_value = get_env_value(var_name, env);
			free(var_name);

			if (var_value)
			{
				
				size_t value_len = ft_strlen(var_value);
				ft_memcpy(res_ptr, var_value, value_len);
				res_ptr += value_len;
			}
			
		}
		else
		{
			
			*res_ptr++ = *ptr++;
		}
	}

	*res_ptr = '\0'; 
	return result;
}


void expand_values_in_tokens(t_data *data)
{
	t_token *current = data->tok;

	while (current)
	{
		
		if (current->to_expand)
		{
			char *expanded_value = replace_variable(current->value, data->env);
			free(current->value); 
			current->value = expanded_value; 
		}

		
		current = current->next;
	}
}

void restore_spaces_in_words(t_data *data)
{
	t_token *current = data->tok;

	while (current)
	{
		
		for (size_t i = 0; current->value[i]; i++)
		{
			if (current->value[i] == '\x01') 
				current->value[i] = ' ';    
		}

		
		current = current->next;
	}
}



void	parsing_tokens(t_data *data)
{
	
	restore_spaces_in_words(data);
	
	check_if_expand_values(data);

	expand_values_in_tokens(data);

	print_tokens(data->tok);


	
	
	
}


// if (!check_pipe_syntax(data->tok, data))
	// 	ft_parsing_error(data);
	// data->ast = create_tree(&data->tok, data);
	// if (data->parsing_error)
	// 	ft_parsing_error(data);
	// if (data->ast != NULL)
	// {
	// 	printf("AST constructed, printing...\n");
	// 	print_ast(data->ast, 0);
	// 	free_ast(&data->ast, data);
	// }