/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:51:31 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/25 18:21:30 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    handle_redir(t_cmd *cmd, t_data *data)
{
    t_redir *tmp;

    while (is_redirection(data->tok))
    {
        data->tok = data->tok->next;
        if (!data->tok || data->tok->type != T_WORD)
            return((data->error_msg = ERR_SYN), false);
        tmp = ft_create_redir_node(data->tok->type, data->tok->value);
        if (!tmp)
            return ((data->error_msg = ERR_MEM), false);
        ft_append_redir(cmd, tmp);
        data->tok = data->tok->next;
    }
    return (true);
}

bool    join_words(char **argv, t_data *data)
{
    printf("JE SUIS DANS JOIN WORDS\n");
    //char *tmp;
    //t_token *current;

    if (data->error_msg)
        return (false);
    // if (!*argv)
    //     *argv = ft_strdup("");
    // if (!*argv)
    //     return (false);
    //current = data->tok;
    print_tab(argv);
    // while(current->type == T_WORD)
    // {
    //     tmp = ft_strdup(*argv);
    //     printf("%s\n", data->tok->value);
    //     *argv = ft_strjoin(*argv, " ");
    //     *argv = ft_strjoin(*argv, current->value);
    //     if (!*argv)
    //         return(free(tmp), false);
    //     free(tmp);
    //     current = current->next;
    // }
    return (true);
}
// handle parsing errors!!!
t_ast_node  *simple_command(t_data *data)
{
    t_ast_node  *node;
    t_token     *current;
    
    if(data->error_msg)
        return (NULL);
    current = data->tok;
    node = ft_create_node(NODE_CMD);
    if (!node)
        return (NULL); // add error message
    // Pourquoi une boucle pour une commande simple ?
    while (current && (current->type == T_WORD  || is_redirection(current)))
    {
        if (current->type == T_WORD)
        {
            if (!join_words(node->cmd->argv, data))
                return (NULL);
        }
        // else if (is_redirection(data->tok))
        // {
        //     if (!handle_redir(node->cmd, data))
        //         return (free(node->cmd->argv), free(node), NULL);
        // }
        //current = current->next;
    }
    return (node);
}