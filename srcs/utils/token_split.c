#include "../inc/minishell.h"
#include <stdbool.h>

//If it is in "quotes" it will skip the spaces without counting them
static size_t count_words(char const *line, char c)
{
	size_t count;
	size_t i;
	bool in_quotes;

	count = 0;
	i = 0;
	in_quotes = false;
	while (*(line + i))
	{
		if (*(line + i) == '"')
			in_quotes = true;
		if (*(line + i) != c || in_quotes)
		{
			if (*(line + i) != c)
			{
				count++;
				while (*(line + i) && (*(line + i) != c || in_quotes))
				{
					if (*(line + i) == '"')
						in_quotes = false;
					i++;
				}
			}
		}
		else
			i++;
	}
	return (count);
}

static size_t get_word_len(char const *line, char c)
{
	size_t i;
	bool in_quotes;

	i = 0;
	in_quotes = false;
	while (*(line + i) && (*(line + i) != c || in_quotes))
	{
		if (*(line + i) == '"')
			in_quotes = true;
		i++;
	}
	return (i);
}

static void free_array(int i, char **array)
{
	while (i >= 0)
	{
		free(*(array + i));
		i--;
	}
	free(array);
}

static char **ft_split1(char const *line, char c, char **array, size_t words_count)
{
	size_t i;
	size_t j;
	bool in_quotes;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		in_quotes = false;
		while (*(line + j) && (*(line + j) == c && !in_quotes))
			j++;
		*(array + i) = ft_substr(line, j, get_word_len((const char *)(line + j), c));
		if (!*(array + i))
			return (free_array(i, array), NULL);
		while (*(line + j) && (*(line + j) != c || in_quotes))
		{
			if (*(line + j) == '"')
				in_quotes = true;
			j++;
		}
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char **ft_token_split(char *line)
{
	char **array;
	size_t words;
	char c;

	c = ' ';
	if (!line)
		return (NULL);
	words = count_words(line, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (free(array), NULL);
	array = ft_split1(line, c, array, words);
	return (array);
}
