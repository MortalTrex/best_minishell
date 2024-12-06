/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_list_malloc_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/12/06 22:29:16 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_shell_list(t_shell_list *head)
{
	t_shell_list	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

static t_shell_list	*ft_allocate_new_node_shell_list(void)
{
	t_shell_list	*new_node;

	new_node = malloc(sizeof(t_shell_list));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_shell_list));
	return (new_node);
}

void	ft_allocate_shell_list(t_data *data, int total_commands)
{
	t_shell_list	*head;
	t_shell_list	*prev;
	t_shell_list	*new_node;
	int				i;

	head = NULL;
	prev = NULL;
	i = 0;
	while (i < total_commands)
	{
		new_node = ft_allocate_new_node_shell_list();
		if (!new_node)
			ft_error_exit(data, ERR_MALLOC);
		if (prev)
		{
			prev->next = new_node;
			new_node->prev = prev;
		}
		if (i == 0)
			head = new_node;
		prev = new_node;
		i++;
	}
	data->shell_list = head;
}
