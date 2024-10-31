/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/30 20:54:15 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_detect_builtin(t_data *data)
{
	t_token	*current;

	current = data->tok;
	while (current)
	{
		printf("current->value: %s\n", current->value);
		if (current->type == T_WORD)
		{
			if (!ft_strcmp(current->value, "cd"))
			{
				ft_cd(data);
				return ;
			}
			else if (!ft_strcmp(current->value, "echo"))
			{
				current->type = T_BUILTIN;
				ft_echo(data);
			}
			else if (!ft_strcmp(current->value, "pwd"))
			{
				ft_pwd();
			}
			else if (!ft_strcmp(current->value, "export"))
			{
				ft_export(data);
			}
			else if (!ft_strcmp(current->value, "unset"))
			{
				ft_unset(data);
			}
			else if (!ft_strcmp(current->value, "env"))
			{
				ft_env(data);
			}
			else if (!ft_strcmp(current->value, "exit"))
				ft_exit(data);
		}
		if (current)
			current = current->next;
	}
}

t_token	*get_tokens(char *command, t_data *data)
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
			ok = ft_append_word(&command, &tokens, data);
	}
	return (tokens);
}

bool	ft_tokenize(t_data *data)
{
	char	*command;

	command = data->user_line;
	data->tok = get_tokens(command, data);
	ft_detect_builtin(data);
	return (true);
}
