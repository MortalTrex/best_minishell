/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:13:13 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/27 16:58:33 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_tokens_to_cmd_array(t_token *tokens)
{
	char	**cmd_array;
	int		i;

	cmd_array = malloc((count_not_null_tokens(tokens) + 1) * sizeof(char *));
	if (!cmd_array)
		return (NULL);
	i = -1;
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->value && tokens->type == T_WORD)
		{
			if (tokens->value[0] != '\0')
				cmd_array[++i] = ft_strdup(tokens->value);
			else
				cmd_array[++i] = ft_strdup("");
			if (!cmd_array[i])
				return (ft_free_tab(cmd_array), NULL);
		}
		tokens = tokens->next;
	}
	cmd_array[++i] = NULL;
	return (cmd_array);
}

bool	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd)
			|| !ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd)
			|| !ft_strcmp("unset", cmd) || !ft_strcmp("env", cmd)
			|| !ft_strcmp("exit", cmd))
			return (true);
		i++;
	}
	return (false);
}

int	parsing(t_data *data)
{
	t_token		*temp;
	t_cmd		*new_command;

	temp = data->tokens;
	data->commands = NULL;
	while (temp)
	{
		if (temp->type != T_PIPE)
		{
			new_command = get_command(temp);
			if (!new_command)
				return (ft_free_cmds(&data->commands), -1);
			add_command_back(&data->commands, new_command);
			temp = get_next_pipe(temp);
			if (!temp)
				break ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
