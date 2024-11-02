/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:05:38 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/02 18:57:41 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && !ft_is_quote(str[*i]) && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*ft_get_dquote_string(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_get_squote_string(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_dquotes(char *str, size_t *i, t_data *data)
{
	char	*tmp;

	tmp = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			tmp = ft_strjoin_free(tmp, ft_expand_env_vars(str, i, data));
		else
			tmp = ft_strjoin_free(tmp, ft_get_dquote_string(str, i));
	}
	(*i)++;
	return (ft_strjoin_free(tmp, ft_strdup("\"")));
}

char	*ft_clean_command(char *str, t_data *data)
{
	char	*command;
	size_t	i;

	command = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			command = ft_strjoin_free(command, ft_get_squote_string(str, &i));
		else if (str[i] == '"')
			command = ft_strjoin_free(command, \
						ft_handle_dquotes(str, &i, data));
		else if (str[i] == '$')
			command = ft_strjoin_free(command, \
						ft_expand_env_vars(str, &i, data));
		else
			command = ft_strjoin_free(command, ft_get_str(str, &i));
	}
	return (command);
}
