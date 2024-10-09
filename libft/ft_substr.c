/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:24:07 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/09 16:32:24 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (!slen || start > slen - 1)
		return (ft_strdup(""));
	i = 0;
	while (s[start + i] && i + 1 <= len)
		i++;
	substr = ft_calloc((i + 1), sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/*
#include <stdio.h>
int	main(void)
{
	int		i;
	char	*str = "";
	char	*string;

	string = ft_substr(str, 3, 5);
	i = 0;
	while (i<5)
	{
		printf("%c\n", string[i]);
		i++;
	}
	return (0);
}*/
