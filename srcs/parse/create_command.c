/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:23:05 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/21 16:55:34 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_not_null_tokens(t_token *tokens)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = tokens;
	if (temp->type == T_PIPE)
		temp = temp->next;
	while (temp && temp->type != T_PIPE)
	{
		if (temp->value)
			count++;
		temp = temp->next;
	}
	return (count);
}

char	**tokens_to_command_array(t_token *tokens)
{
	char	**cmd_array;
	int		i;

	i = -1;
	cmd_array = malloc((count_not_null_tokens(tokens) + 1) * sizeof(char *));
	if (cmd_array == NULL)
		return (NULL);
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->value && tokens->value[0] != '\0' && tokens->type == T_WORD)
		{
			cmd_array[++i] = ft_strdup(tokens->value);
			if (cmd_array[i] == NULL)
				return (ft_free_tab(cmd_array), NULL);
		}
		else if (tokens->value && tokens->type == T_WORD)
		{
			cmd_array[++i] = ft_strdup("");
			if (cmd_array[i] == NULL)
				return (ft_free_tab(cmd_array), NULL);
		}
		tokens = tokens->next;
	}
	cmd_array[++i] = NULL;
	return (cmd_array);
}

t_cmd   *get_last_arg(t_cmd *command_args)
{
    if(!command_args)
        return (NULL);
    while (command_args->next)
        command_args = command_args->next;
    return (command_args);
}

t_cmd   add_to_back(t_cmd **command_arguments, t_cmd *new_arg)
{
    t_cmd  *tmp;

    if (!new_arg)
        return ;
    if (*command_arguments && new_arg)
    {
        tmp = get_last_arg(*command_arguments);
        tmp->next = new_arg;
        new_arg->prev = tmp;
        new_arg->next = NULL;
    }
    else
    {
        *command_arguments = new_arg;
        (*command_arguments)->next = NULL;
        (*command_arguments)->prev = NULL;
    }
}
t_cmd *create_command(t_token *token)
{
    t_cmd *command;

    if(!token)
        return (NULL);
    command = malloc(sizeof(t_cmd));
    if(!command)
        return (NULL);
    ft_memset(command, 0, sizeof(t_cmd));
    command->cmd_args = tokens_to_command_array(token);
    handle_redirections(token, command);
    if(command->cmd_args && command->cmd_args[0])
        command->is_builtin = is_builtin(command->cmd_args[0]);
    return(command);
}