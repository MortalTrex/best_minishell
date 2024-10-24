/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:39:59 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/24 18:06:01 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// error message handling

t_ast_node    *create_tree(t_data *data)
{
    t_ast_node	*right;
    t_ast_node  *left;

    if (!data->tmp_token)
        return (NULL);
    left = simple_command(data);
    if (!left)
        return (NULL);
    while (data->tmp_token && data->tmp_token->type == T_PIPE)
    {
        data->tmp_token = data->tmp_token->next;
        if (!data->tmp_token || data->tmp_token->type != T_WORD)
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