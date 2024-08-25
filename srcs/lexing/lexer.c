#include "minishell.h"

t_token	*ft_lexer(char *line)
{
	char **tokens;
	int i = 0;

	tokens = ft_split_ms(line);
	while(tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	free(tokens);
	return (NULL);
}
