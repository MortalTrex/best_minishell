
#include "minishell.h"

static size_t	count_words(char const *s)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		if (!isspace(*(s + i)))
		{
			count++;
			while (*(s + i) && !(ft_isspace(*(s + i))))
				i++;
		}
		else if (ft_isspace(*(s + i)))
			i++;
	}
	return (count);
}

static size_t	get_word_len(char const *s)
{
	size_t	i;

	i = 0;
	while (*(s + i) && !ft_isspace(*(s + i)))
		i++;
	return (i);
}

static void	free_array(int i, char **array)
{
	while (i >= 0)
	{
		free(*(array + i));
		i--;
	}
	free(array);
}

static char	**ft_split1(char const *s, char **array, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (*(s + j) && ft_isspace(*(s + j)))
			j++;
		*(array + i) = ft_substr(s, j, get_word_len((const char *)(s + j)));
		if (!*(array + i))
			return (free_array(i, array), NULL);
		while (*(s + j) && !ft_isspace(*(s + j)))
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char	**ft_split_ms(char const *s)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (free(array), NULL);
	array = ft_split1(s, array, words);
	return (array);
}

