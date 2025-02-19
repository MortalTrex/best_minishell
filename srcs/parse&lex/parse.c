/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:13:13 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/19 13:11:21 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_pipe_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token)
	{
		if (token->type == T_PIPE)
			return (token);
		token = token->next;
	}
	return (NULL);
}

int parse(t_data *data)
{
    t_token *token;
    t_cmd *command;

    token = data->tokens;
    data->commands = NULL;
    while (token)
    {
        if (token->type != T_PIPE)
        {
            command = create_command(token, data);
            if (!command)
                return (1); //  add free !!! error
            add_to_back(&data->commands, command);
            token = get_next_pipe_token(token);
            if (!token)
                break;
        }
        token = token->next;
    }
    return (EXIT_SUCCESS);
}