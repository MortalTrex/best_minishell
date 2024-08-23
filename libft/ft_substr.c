/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:24:07 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/08/23 19:08:55 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*str;
	int	i;
	int	j;

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
	while (i < (int)(ft_strlen(s)) && j < len)
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
