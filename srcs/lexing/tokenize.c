/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/04 17:16:35 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_tokens(char *command, t_data *data)
{
	t_token	*tokens;
	bool	ok;

	ok = true;
	tokens = NULL;
	if (!command)
		return (NULL);
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
	return (true);
}
