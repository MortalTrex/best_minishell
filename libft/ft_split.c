/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:57:45 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 18:15:37 by mmiilpal         ###   ########.fr       */
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

static void	ft_freetab(int i, char **array)
{
	while (i >= 0)
	{
		free(*(array + i));
		i--;
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
			return (ft_freetab(i, array), NULL);
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
		return (free(array), NULL);
	array = ft_split1(s, c, array, words);
	return (array);
}

// int	main(void)
// {
// 	char	*s;
// 	char	**res;
// 	int		i;

//   s = "salutca-va";
//   res = ft_split(s, '-');
//   i = 0;
//   while(res[i])
//   {
// 	printf("%s", res[i]);
// 	i++;
//   }
//   free(res);
// }