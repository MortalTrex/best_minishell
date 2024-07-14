/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:24:07 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/29 12:59:26 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = (char *) malloc (sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
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
