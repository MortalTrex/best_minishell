/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:13:13 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/17 16:24:48 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse(t_data *data)
{
    t_token *token;
    t_cmd *command;

    token = data->tok;
    data->commands = NULL;
    while (token)
    {
        if (token->type != T_PIPE)
        {
            command = create_command(token, data);
        }
        
    }
      
    
}