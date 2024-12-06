/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/12/06 17:57:18 by dagudelo         ###   ########.fr       */
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



int count_total_commands(t_data *data)
{
	int total_commands = 0;
	t_token *current = data->tok;

	while (current)
	{
		if (current->type == T_PIPE)
			total_commands++;
		current = current->next;
	}
	return total_commands + 1;
}


int count_total_redirs(t_token *current)
{
	int total_redirs = 0;

	while (current)
	{
		if (current->type == T_PIPE)
			break;
		
		if (current->type == T_REDIR_IN || current->type == T_REDIR_OUT || current->type == T_REDIR_APPEND || current->type == T_REDIR_HERE)
			total_redirs++;
		current = current->next;
	}
	return total_redirs;
}

void ft_free_shell_list(t_shell_list *head)
{
    while (head)
    {
        t_shell_list *next = head->next;
        free(head);
        head = next;
    }
}


t_shell_list *ft_allocate_new_node_shell_list(void)
{
    t_shell_list *new_node = malloc(sizeof(t_shell_list));
    if (!new_node)
        return NULL; 

    ft_bzero(new_node, sizeof(t_shell_list));
    return new_node; 
}


void ft_allocate_shell_list(t_data *data, int total_commands)
{
    t_shell_list *head = NULL;
    t_shell_list *prev = NULL;

    for (int i = 0; i < total_commands; i++)
    {
        
        t_shell_list *new_node = ft_allocate_new_node_shell_list();
        if (!new_node)
        {
            
            ft_free_shell_list(head);
            ft_error(data, ERR_MALLOC);
            return;
        }

        
        if (prev)
        {
            prev->next = new_node;
            new_node->prev = prev;
        }

        
        if (i == 0)
            head = new_node;

        prev = new_node; 
    }

    
    data->shell_list = head;
}

t_redir *ft_allocate_new_node_redir(void)
{
    t_redir *new_node = malloc(sizeof(t_redir));
    if (!new_node)
        return NULL;

    ft_bzero(new_node, sizeof(t_redir));
    return new_node;
}

void ft_free_redir_list(t_redir *head)
{
    while (head)
    {
        t_redir *next = head->next;
        if (head->value)
            free(head->value); 
        free(head); 
        head = next;
    }
}

t_redir_type get_type_redir(t_token_type type)
{
	if (type == T_REDIR_IN)
		return IN;
	else if (type == T_REDIR_OUT)
		return OUT;
	else if (type == T_REDIR_APPEND)
		return D_APPEND;
	else if (type == T_REDIR_HERE)
		return D_HEREDOC;
	
	return -1;
}

void ft_allocate_redirs(t_redir **current, t_token *current_token, t_data *data)
{
    t_redir *new_node = ft_allocate_new_node_redir();
    if (!new_node)
    {
        ft_free_redir_list(*current); 
        ft_error(data, ERR_MALLOC);
        return;
    }

	t_redir_type type_redir = get_type_redir(current_token->type);
    
    new_node->type = type_redir;
	
	char *value = ft_strdup(current_token->next->value);
	
    new_node->value = ft_strdup(value); 
	
    if (!new_node->value)
    {
        free(new_node); 
        ft_free_redir_list(*current);
        ft_error(data, ERR_MALLOC);
        return;
    }

    
    if (*current == NULL)
    {
        
        *current = new_node;
    }
    else
    {
        
        t_redir *last = *current;
        while (last->next)
            last = last->next;

        last->next = new_node;
        new_node->prev = last;
    }
}


void ft_allocate_redirs_main(t_shell_list *shell_list, t_data *data)
{
    t_shell_list *current = shell_list;
    t_token *current_token = data->tok;

    while (current)
    {
        while (current_token)
        {
            if (current_token->type == T_PIPE)
            {
                current_token = current_token->next;
                break;
            }
            if (current_token && 
                (current_token->type == T_REDIR_IN || 
                 current_token->type == T_REDIR_OUT || 
                 current_token->type == T_REDIR_APPEND || 
                 current_token->type == T_REDIR_HERE))
            {
                ft_allocate_redirs(&current->redir, current_token, data);
            }
            current_token = current_token->next;
        }
        current = current->next;
    }
}



void print_shell_list(t_data *data)
{
	t_shell_list *current = data->shell_list;
	int i = 0;

	while (current)
	{
		printf("%sCommand %d: %s%s\n", BLUE, i, current->command, RESET);
		printf("%sArgv: ", GREEN);
		while (current->argv && *current->argv)
		{
			printf("%s ", *current->argv);
			current->argv++;
		}
		printf("\n%s", RESET);
		// printf("PID: %d\n", current->pid);
		printf("%sRedirs:\n", YELLOW);
		t_redir *redir = current->redir;
		while (redir)
		{
			if (redir->type == IN)
				printf("Type: IN\n");
			else if (redir->type == OUT)
				printf("Type: OUT\n");
			else if (redir->type == D_APPEND)
				printf("Type: D_APPEND\n");
			else if (redir->type == D_HEREDOC)
				printf("Type: D_HEREDOC\n");
			printf("File: %s\n", redir->value);
			redir = redir->next;
		}
		printf("%s", RESET);
		current = current->next;
		i++;
	}
}

char **ft_append_to_argv(char **argv, char *value)
{
    size_t count = 0;

    if (argv)
    {
        while (argv[count])
            count++;
    }

    char **new_argv = malloc(sizeof(char *) * (count + 2));
    if (!new_argv)
        return NULL;

    for (size_t i = 0; i < count; i++)
    {
        new_argv[i] = argv[i];
    }

    new_argv[count] = ft_strdup(value);
    if (!new_argv[count])
    {
        free(new_argv);
        return NULL;
    }

    new_argv[count + 1] = NULL;

    if (argv)
        free(argv);

    return new_argv;
}


void ft_fill_shell_list(t_data *data)
{
	t_shell_list *current = data->shell_list;
	t_token *current_token = data->tok;

	while (current)
	{
		while (current_token)
		{
			if (current_token->type == T_PIPE)
			{
				current_token = current_token->next;
				break;
			}

			if (current_token->type == T_CMD)
				current->command = ft_strdup(current_token->value);

			if (current_token->type == T_ARG)
				current->argv = ft_append_to_argv(current->argv, current_token->value);
			
			current_token = current_token->next;
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
	int total_commands = 0;
	int total_redirs = 0;
	total_commands = count_total_commands(data);
	total_redirs = count_total_redirs(data->tok);
	printf("%sTotal commands: %d%s\n", GREEN, total_commands, RESET);
	printf("%sTotal redirs: %d%s\n", GREEN, total_redirs, RESET);
	ft_allocate_shell_list(data , total_commands);
	ft_allocate_redirs_main(data->shell_list, data);
	ft_fill_shell_list(data);
	print_shell_list(data);
}
