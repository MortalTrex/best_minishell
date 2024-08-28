#include "minishell.h"

bool	analyze_line(bool is_quotes, char *line, t_token **tokens,
		unsigned int i)
{
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
				ft_append_operator(tokens, line, &i);
			else
				ft_append_word(tokens, line, &i);
		}
	}
	return (is_quotes);
}

bool	ft_tokenize(char *line, t_token **tokens)
{
	unsigned int	i;
	bool			is_quotes;

	i = 0;
	is_quotes = analyze_line(false, line, tokens, i);
	if (is_quotes == true)
		return (ft_printf("Error: Unclosed quotes\n"), false);
	ft_stackadd_back(tokens, ft_stacknew(T_EOF, NULL));
	return (true);
}
