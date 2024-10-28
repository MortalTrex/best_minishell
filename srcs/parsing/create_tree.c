/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:39:59 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/28 14:13:54 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// error message handling

t_ast_node    *create_tree(t_data *data)
{
    t_ast_node	*right;
    t_ast_node  *left;
    t_token     *current;

    if (!data->tok)
        return (NULL);
    current = data->tok;
    printf("RENTRE DANS LARBRE\n");
    left = simple_command(data);
    if (!left)
        return (NULL);
    while (current && current->type == T_PIPE)
    {
        current = current->next;
        if (!current || current->type != T_WORD)
            return (data->error_msg = ERR_SYN, left);
        right = simple_command(data);
        if (!right)
            return (left);
        left = ft_create_pipe_node(left, right);
        if (!left)
            return (free_ast(left), free_ast(right), NULL); // add frees for left and right ast
    }
    return (left);
}
