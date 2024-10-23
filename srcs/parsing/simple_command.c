/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:51:31 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/23 19:20:30 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    handle_redir(t_redir **redir, t_cmd *cmd, t_data *data)
{
    t_redir *tmp;

    while (is_redirection(data.tmp_token->type))
    {
        data.tmp_token = data.tmp_token->next;
        if (!data.tmp_token || data.tmp_token->type != T_WORD)
            return((data->error_msg == ERR_SYN), false);
        tmp = ft_create_redir_node(data.tmp_token->type, data.tmp_token->value);
        if (!tmp)
            return ((data->error_msg == ERR_MEM), false);
        ft_append_redir(cmd, tmp);
        data.tmp_token = data.tmp_token->next;
    }
    return (true);
}

bool    join_words(char **argv, t_data *data)
{
    char *tmp;

    if (data->error_msg)
        return (false);
    if (!*argv)
        *argv = ft_strdup("");
    if (!*argv)
        return (false);
    while(data.tmp_token->type == T_WORD)
    {
        tmp = *argv;
        *argv = ft_strjoin(*argv, " ");
        *argv = ft_strjoin(*argv, data.tmp_token->value);
        if (!*argv)
            return(free(tmp), false);
        free(tmp);
        data.tmp_token = data.tmp_token->next;
    }
    return (true);
}
// handle parsing errors!!!
t_ast_node  *simple_command(t_data *data)
{
    t_ast_node  *node;

    node = ft_create_node(NODE_CMD);
    if (!node)
        return (NULL); // add error message
    while (data.tmp_token && (data.tmp_token->type == T_WORD  || is_redirection(data.tmp_token->type)))
    {
        if (data.tmp_token->type == T_WORD)
        {
            if (!join_words(&(node->cmd->argv), data.tmp_token->value, data))
                return (data.error_msg == E_MEM, NULL);
        }
        else if (is_redirection(data.tmp_token->type))
        {
            if (!handle_redir(&(node->cmd->redir), &(node->cmd), data))
                return (free(node), free(node->cmd->argv), NULL);
        }
    }
    return (node);
}