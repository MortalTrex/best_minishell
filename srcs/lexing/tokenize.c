/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/09 18:01:13 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_detect_builtin(t_token **tokens, t_data *data)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == T_WORD)
		{
			if (!ft_strcmp(current->value, "cd"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "echo"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "pwd"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "export"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "unset"))
				current->type = T_BUILTIN;
			else if (!ft_strcmp(current->value, "env")) 
			{
				current->type = T_BUILTIN;
				ft_env(data);
			}
			else if (!ft_strcmp(current->value, "exit"))
				current->type = T_BUILTIN;
		}
		current = current->next;
	}
}

bool	ft_tokenize(char *line, t_token **tokens, t_data *data)
{
	unsigned int	i;
	bool			is_double_quotes;
	bool			is_single_quotes;

	i = 0;
	is_double_quotes = false;
	is_single_quotes = false;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
		{
			is_double_quotes = !is_double_quotes;
			i++;
		}
		else if (line[i] == '\'')
		{
			is_single_quotes = !is_single_quotes;
			i++;
		}
		else if (is_double_quotes == true)
			ft_append_word_dquotes(tokens, line, &i);
		else if (is_single_quotes == true)
			ft_append_word_squotes(tokens, line, &i);
		else if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '$')
			ft_append_env_var(tokens, line, &i);
		else if (ft_is_operator(line[i]))
		{
			ft_append_operator(tokens, line, &i);
			if (line[i] != '\0' && ft_is_operator(line[i]))
				return (fprintf(stderr,
						"Error: Unexpected operator sequence\n"), false);
		}
		else if (!ft_append_word(tokens, line, &i))
			return (false);
	}
	if (is_double_quotes == true || is_single_quotes == true)
		return (ft_msg_free_exit("Error: Unclosed quotes\n", tokens), false);
	ft_detect_builtin(tokens, data);
	return (ft_stackadd_back(tokens, ft_stacknew(T_EOF, NULL)), true);
}
