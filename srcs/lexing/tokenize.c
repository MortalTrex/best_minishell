/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/04 18:46:51 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_tokenize(char *line, t_token **tokens)
{
	unsigned int	i;
	bool			is_quotes;

	i = 0;
	is_quotes = false;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
		{
			is_quotes = !is_quotes;
			i++;
		}
		else if (is_quotes == true)
			ft_append_word_quotes(tokens, line, &i);
		else
		{
			if (ft_isspace(line[i]))
				i++;
			else if (ft_is_operator(line[i]))
			{
				ft_append_operator(tokens, line, &i);
				if (line[i] != '\0' && ft_is_operator(line[i]))
				{
					fprintf(stderr, "Error: Unexpected operator sequence\n");
					return (false);
				}
			}
			else
			{
				if (!ft_append_word(tokens, line, &i))
					return (false);
			}
		}
	}
	if (is_quotes == true)
		return (ft_msg_free_exit("Error: Unclosed quotes\n", tokens), false);
	ft_stackadd_back(tokens, ft_stacknew(T_EOF, NULL));
	return (true);
}
