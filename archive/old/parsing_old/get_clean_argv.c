/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clean_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:05:25 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/02 18:05:29 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_skip_word(char const *s, size_t	*i)
{
	char	quotes;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			quotes = s[(*i)++];
			while (s[(*i)] != quotes)
				(*i)++;
			(*i)++;
		}
	}
}

static char	**ft_allocater(char const *s, char **strs)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			start = i;
			ft_skip_word(s, &i);
			strs[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!strs[j])
				return (NULL);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

static void	ft_words_filler(const char *s, char **strs, size_t *i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (s[(*i)] && s[(*i)] != ' ')
	{
		if (s[(*i)] != '\'' && s[(*i)] != '"')
			strs[j][k++] = s[(*i)++];
		else
		{
			quotes = s[(*i)++];
			strs[j][k++] = quotes;
			while (s[(*i)] != quotes)
				strs[j][k++] = s[(*i)++];
			strs[j][k++] = s[(*i)++];
		}
	}
}

static char	**ft_filler(char const *s, char **strs)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && strs[j])
	{
		if (s[i] != ' ')
		{
			ft_words_filler(s, strs, &i, j);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

char	**ft_ms_split(char const *str)
{
	size_t		count;
	char		**strs;
	char		**tmp;
	size_t		i;

	if (!str)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ' && ++count)
			ft_skip_word(str, &i);
		while (str[i] && str[i] == ' ')
			i++;
	}
	strs = ft_calloc(count + 1, sizeof(char *));
	tmp = strs;
	strs = ft_allocater(str, strs);
	if (!strs || !count)
		return (ft_free_tab(tmp), NULL);
	return (ft_filler(str, strs));
}
