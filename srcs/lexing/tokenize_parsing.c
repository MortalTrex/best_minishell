/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 21:19:10 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_find_match_tokens(t_match_tokens *match, const char **tokens,
		const char **prompt)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		match->token_len = ft_strlen(tokens[i]);
		if (ft_strncmp(*prompt, tokens[i], match->token_len) == 0)
		{
			if (match->dest != match->new_prompt && *(match->dest - 1) != ' ')
				*match->dest++ = ' ';
			ft_strncpy(match->dest, tokens[i], match->token_len);
			match->dest += match->token_len;
			if (*(*prompt + match->token_len) != ' ')
				*match->dest++ = ' ';
			*prompt += match->token_len;
			match->matched = true;
			return ;
		}
		i++;
	}
}

char	*ft_add_spaces_around_tokens(const char *prompt)
{
	static const char	*tokens[] = {"=", "<<", ">>", "<", ">", "|", NULL};
	t_match_tokens		match;

	match.new_prompt = malloc(ft_strlen(prompt) * 2 + 1);
	if (!match.new_prompt)
		return (NULL);
	match.dest = match.new_prompt;
	while (*prompt)
	{
		match.matched = false;
		ft_find_match_tokens(&match, tokens, &prompt);
		if (!match.matched)
			*match.dest++ = *prompt++;
	}
	*match.dest = '\0';
	return (match.new_prompt);
}

static void	ft_hex_to_espaces(char *result, bool in_single_quotes,
		bool in_double_quotes)
{
	size_t	i;

	i = 0;
	if (in_single_quotes || in_double_quotes)
	{
		while (result[i])
		{
			if (result[i] == '\x01')
				result[i] = ' ';
			i++;
		}
	}
}

char	*ft_replace_spaces_in_quotes(const char *prompt)
{
	char	*result;
	bool	in_single_quotes;
	bool	in_double_quotes;
	size_t	i;

	result = ft_strdup(prompt);
	if (!result)
		return (NULL);
	in_single_quotes = false;
	in_double_quotes = false;
	i = 0;
	while (result[i])
	{
		if (result[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (result[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if ((in_single_quotes || in_double_quotes) && result[i] == ' ')
			result[i] = '\x01';
		i++;
	}
	ft_hex_to_espaces(result, in_single_quotes, in_double_quotes);
	return (result);
}
