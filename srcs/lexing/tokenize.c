#include "minishell.h"

void ft_append_operator(t_token **tokens, char *line, unsigned int *i)
{
	t_token *new;

	new = NULL;
	if (line[*i] == '|')
		new = ft_stacknew(T_OPERATOR, &line[*i]);
	else if (line[*i] == ';')
		new = ft_stacknew(T_OPERATOR, &line[*i]);
	else
	{
		if (line[*i + 1] == '>' && line[*i] == '>')
		{
			new = ft_stacknew(T_OPERATOR, ">>");
			(*i)++;
		}
		else if (line[*i] == '<' && line[*i + 1] == '<')
		{
			new = ft_stacknew(T_OPERATOR, "<<");
			(*i)++;
		}
		else
			new = ft_stacknew(T_OPERATOR, &line[*i]);
	}
	ft_stackadd_back(tokens, new);
}

void ft_append_word(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int start = *i;
	int len = 0;
	t_token *new;

	if (line [*i] == '\'' || line[*i] == '\"')
	{
		(*i)++;
		len++;
		while (line[*i] && line[*i] != line[start])
		{
			(*i)++;
			len++;
		}
		if (line[*i] == line[start])
		{
			(*i)++;
			len++;
		}
	}
	else if (line[*i] && !ft_isspace(line[*i]) && !ft_isoperator(line[*i]))
	{
		(*i)++;
		len++;
		while (line[*i] && !ft_isspace(line[*i]) && !ft_isoperator(line[*i]))
		{
			(*i)++;
			len++;
		}
	}
	char *substr = ft_substr(line, start, len);
	if (!substr)
	{
		fprintf(stderr, "Error: ft_substr returned NULL\n");
		return;
	}
	new = ft_stacknew(T_WORD, substr);
	if (!new)
	{
		fprintf(stderr, "Error: ft_stacknew returned NULL\n");
		free(substr);
		return;
	}
	ft_stackadd_back(tokens, new);
}

void ft_append_word_space(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int start = *i;
	int len = 0;
	t_token *new;

	while (line[*i] && line[*i] != '"')
	{
		(*i)++;
		len++;
	}
	char *substr = ft_substr(line, start, len);
	if (!substr)
	{
		fprintf(stderr, "Error: ft_substr returned NULL\n");
		return;
	}
	new = ft_stacknew(T_WORD, substr);
	if (!new)
	{
		fprintf(stderr, "Error: ft_stacknew returned NULL\n");
		free(substr);
		return;
	}
	ft_stackadd_back(tokens, new);
}

bool ft_tokenize(char *line, t_token **tokens)
{
	unsigned int	i;
	bool			is_quotes;	

	i = 0;
	is_quotes = false;

	while (line[i] != '\0')
	{
		if (line[i] == '"')
		{
			is_quotes = !is_quotes;
			i++;
		}
		else if (is_quotes == true)
			ft_append_word_space(tokens, line, &i);
		else
		{
			if (ft_isspace(line[i]))
				i++;
			else if (ft_isoperator(line[i]))
				ft_append_operator(tokens, line, &i);
			else
				ft_append_word(tokens, line, &i);
		}
	}
	if (is_quotes == true)
	{
		ft_printf("Error: Unclosed quotes\n");
		return (false);
	}
	ft_stackadd_back(tokens, ft_stacknew(T_EOF, NULL));
	return (true);
}
