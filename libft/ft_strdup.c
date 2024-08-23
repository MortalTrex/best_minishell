/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:04:37 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/08/23 18:37:00 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	if (ft_strlen(s) == 0)
	{
		dest = (char *) malloc (1 * sizeof(char));
		if (!dest)
			return (free(dest), NULL);
		dest[0] = '\0';
		return (dest);
	}
	dest = (char *) malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (free(dest), NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc)
	{
		printf("%s\n", ft_strdup(argv[1]));
		printf("%s\n", strdup(argv[1]));
	}
	return (0);
}*/
