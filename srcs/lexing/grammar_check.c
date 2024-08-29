#include "minishell.h"

bool	ft_is_operator(char c)
{
	if (c == '|' || c == '(' || c == '>' || c == '<' || c == ')' \
			|| c == '&' )
		return (true);
	return (false);
}

bool	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

bool	ft_skip_quotes(char *line, unsigned int *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

bool	ft_is_wordchar(char c)

{
	if (c == '~' || c == '-' || c == '.' || c == '/' || c == '*' || c == '?' || c == '=')
		return (true);
	else if (ft_isalnum(c) || c == '_' || c == '$')
		return (true);
	else
		return (false);
}
