/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/18 17:22:41 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_detect_builtin(t_data *data)
{
	t_token	*current;

	current = data->tok;
	while (current)
	{
		if (current->type == T_WORD)
		{
			if (!ft_strcmp(current->value, "cd"))
			{
				current->type = T_BUILTIN;
				ft_cd(data);
				return ;
			}
			else if (!ft_strcmp(current->value, "echo"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "pwd"))
			{
				current->type = T_BUILTIN;
				ft_pwd();
			}
			else if (!ft_strcmp(current->value, "export"))
			{
				current->type = T_BUILTIN;
				ft_export(data);
			}
			else if (!ft_strcmp(current->value, "unset"))
			{
				current->type = T_BUILTIN;
				ft_unset(data);
			}
			else if (!ft_strcmp(current->value, "env"))
			{
				current->type = T_BUILTIN;
				ft_env(data);
			}
			else if (!ft_strcmp(current->value, "exit"))
				ft_exit(data);
			// else
			// 	exec_launch(current->value, data);
		}
		if (current)
			current = current->next;
	}
}

t_token *get_tokens(char *command)
{
	t_token	*tokens;
	bool	ok;

	ok = true;
	tokens = NULL;
	while (*command)
	{
		if (ok == false)
			return (ft_stackclear(&tokens), NULL);
		while (ft_isspace(*command) && *command)
			command++;
		if (ft_is_operator(*command))
			ok = ft_append_operator(&command, &tokens);
		else
			ok = ft_append_word(&command, &tokens);
	}
	return (tokens);
}


bool	ft_tokenize(t_data *data)
{
	char *command;

	command = data->user_line;
	data->tok = get_tokens(command);
	return (true);
}

