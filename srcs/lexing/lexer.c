#include "minishell.h"

t_token	*ft_lexer(char *line)
{
	t_token *tokens;

	if (!ft_tokenize(line, &tokens))
		return (ft_stackclear(&tokens), NULL);
	return (tokens);
}
