#include "minishell.h"

static size_t	ft_unquoted_strlen(char *str)
{
	size_t	i;
	size_t	len;
	char	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quotes)
				quotes = str[i++];
			else if (str[i] == quotes)
				quotes = ((i++) && 0);
			else
				len += (i++ || 1);
		}
		else
				len += (i++ || 1);
	}
	return (len);
}

char	*ft_remove_quotes(char *str)
{
	char	*clean;
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	clean = ft_calloc(1 + ft_unquoted_strlen(str), sizeof(char));
	if (!clean)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] != quote)
				clean[j++] = str[i++];
			i++;
		}
		else
			clean[j++] = str[i++];
	}
	return (free(str), clean);
}
