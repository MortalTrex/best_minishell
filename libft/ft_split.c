/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:57:45 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/23 17:14:20 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			count++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else if (*(s + i) == c)
			i++;
	}
	return (count);
}

static size_t	get_word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(*(array + i));
	}
	free(array);
}

static char	**ft_split1(char const *s, char c, char **array, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(array + i) = ft_substr(s, j, get_word_len((const char *)(s + j), c));
		if (!*(array + i))
		{
			free_array(i, array);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = ft_split1(s, c, array, words);
	return (array);
}
/*
// Function to free the memory allocated for the result of ft_split
void free_split_result(char **result) {
    char **temp = result;
    while (*temp) {
        free(*temp);
        temp++;
    }
    free(result);
}

int main() {
    // Example usage
    char input_string[] = "Hello,World,C,Programming";
    char delimiter = ',';

    printf("Input String: %s\n", input_string);
    printf("Delimiter: %c\n", delimiter);

    // Call the ft_split function
    char **result = ft_split(input_string, delimiter);

    // Print the result
    printf("Result:\n");
    for (int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
    }

    // Free the memory allocated for the result
    free_split_result(result);

    return 0;
}*/
