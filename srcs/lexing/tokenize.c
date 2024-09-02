#include "minishell.h"

#include "minishell.h"

void	ft_append_operator(t_token **tokens, char *line, unsigned int *i)
{
	t_token	*new;

    printf("line[%d]: %c\n", *i, line[*i]);
	new = NULL;
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
    (*i)++;
	ft_stackadd_back(tokens, new);
}

bool	ft_append_word(t_token **tokens, char *line, unsigned int *i)
{
	unsigned int start;
    char        *substr;
	int         len;
	t_token     *new;

    len = 0;
    start = *i;
	while (line[*i] && ft_is_wordchar(line[*i]) && !ft_isspace(line[*i]))
	{
		if (ft_is_quote(line[*i]))
		{
			if(!ft_skip_quotes(line, i))
				return (false);
		}
		else
		{
			(*i)++;
			len++;
		}
	}
	substr = ft_substr(line, start, len);
	if (!substr)
		return (fprintf(stderr, "Error: ft_substr returned NULL\n"), false);
	new = ft_stacknew(T_WORD, substr);
	if (!new)
	{
		free(substr);
		return (fprintf(stderr, "Error: ft_stacknew returned NULL\n"), false);
	}
	ft_stackadd_back(tokens, new);
	return (true);
}

void ft_append_word_quotes(t_token **tokens, char *line, unsigned int *i)
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
		return ;
	}
	new = ft_stacknew(T_WORD, substr);
	if (!new)
	{
		fprintf(stderr, "Error: ft_stacknew returned NULL\n");
		free(substr);
		return ;
	}
	ft_stackadd_back(tokens, new);
}

bool ft_tokenize(char *line, t_token **tokens)
{
    unsigned int i = 0;
    bool is_quotes = false;

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
            {
                ft_append_operator(tokens, line, &i);
                if (line[i] != '\0' && ft_is_operator(line[i]))
                {
                    fprintf(stderr, "Error: Unexpected operator sequence\n");
                    return false;
                }
            }
            else
            {
                if (!ft_append_word(tokens, line, &i))
                    return false;
            }
        }
    }
    if (is_quotes == true)
        return (ft_msg_free_exit("Error: Unclosed quotes\n", tokens), false);
    ft_stackadd_back(tokens, ft_stacknew(T_EOF, NULL));
    return true;
}


