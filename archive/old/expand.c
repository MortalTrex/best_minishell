/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:12:49 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 15:09:48 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_value(char *var, t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strcmp(var, current->name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*ft_expand_env_vars(char *word, size_t *i, t_data *data)
{
	char	*env_value;
	char	*var;
	size_t	start;

	(*i)++;
	if (ft_isdigit(word[*i]) || word[*i] == '@')
		return ((*i)++, ft_strdup(""));
	else if (word[*i] == '?')
		return ((*i)++, ft_itoa(data->exit_status));
	else if (!ft_is_wordchar(word[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (ft_is_wordchar(word[*i]))
		(*i)++;
	var = ft_substr(word, start, *i - start);
	env_value = ft_get_env_value(var, data);
	if (!env_value)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_value));
}

int	is_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		if (str[i])
			i++;
	}
	return (0);
}

int	is_expandable(char *str, int i, char *quote)
{
	if (*quote == '\'')
		return (0);
	if (str && is_heredoc(str))
		return (0);
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
			|| str[i + 1] == '?'))
		return (*quote = 0, 1);
	return (0);
}

int find_quote(char c, char *quote)
{
    if (c == '\'' || c == '\"')
    {
        if (!*quote)
            *quote = c;
        else if (*quote == c)
            *quote = 0;
        return(*quote);
    }   
    return (-1);
}

int expansion_count(char *str)
{
    int count;
    
    count = 0;
    while(*str)
    {
        if (*str = '$')
            count++;
        str++;
    }
    return(count);
}

char *expanding(char *str, t_data *data)
{
    char quote;
    int dollars_count;
    
    dollars_count = expansion_count(str);
    quote = 0;
    while (*str)
    {
        find_quote(*str, &quote);
        if(is_expandable(str, *str, &quote) && dollars_count-- > 0)
        {
            str = ft_expand_env_vars(str, &str, data);
            if (!str)
                break;
        }
        else
            str++;
    }
    return (str);
}