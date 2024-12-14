/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_list_malloc_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/12/14 18:13:04 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_allocate_new_node_redir(void)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_redir));
	return (new_node);
}

// void	ft_free_redir_list(t_redir *head)
// {
// 	t_redir	*next;

// 	while (head)
// 	{
// 		next = head->next;
// 		if (head->value)
// 			free(head->value);
// 		free(head);
// 		head = next;
// 	}
// }

t_redir_type	ft_get_type_redir(t_token_type type)
{
	if (type == T_REDIR_IN)
		return (IN);
	else if (type == T_REDIR_OUT)
		return (OUT);
	else if (type == T_REDIR_APPEND)
		return (D_APPEND);
	else if (type == T_REDIR_HERE)
		return (D_HEREDOC);
	return (-1);
}

void	ft_allocate_redirs(t_redir **current, t_token *current_token,
		t_data *data)
{
	t_redir			*new_node;
	t_redir_type	type_redir;
	char			*value;
	t_redir			*last;

	new_node = ft_allocate_new_node_redir();
	if (!new_node)
		ft_error_exit(data, ERR_MALLOC);
	type_redir = ft_get_type_redir(current_token->type);
	new_node->type = type_redir;
	value = ft_strdup(current_token->next->value);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		ft_error_exit(data, ERR_MALLOC);
	if (*current == NULL)
		*current = new_node;
	else
	{
		last = *current;
		while (last->next)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
}

void	ft_allocate_fill_redirs_main(t_shell_list *shell_list, t_data *data)
{
	t_shell_list	*current;
	t_token			*current_token;

	current = shell_list;
	current_token = data->tok;
	while (current)
	{
		while (current_token)
		{
			if (current_token->type == T_PIPE)
			{
				current_token = current_token->next;
				break ;
			}
			if (current_token && (current_token->type == T_REDIR_IN
					|| current_token->type == T_REDIR_OUT
					|| current_token->type == T_REDIR_APPEND
					|| current_token->type == T_REDIR_HERE))
			{
				ft_allocate_redirs(&current->redir, current_token, data);
			}
			current_token = current_token->next;
		}
		current = current->next;
	}
}
