/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:19:59 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/29 13:34:43 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && *(unsigned char *)s1 == *(unsigned char *)s2 && n--)
	{
		s1++;
		s2++;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	int	res;

	if (argc == 4)
	{
		res = ft_strncmp(argv[1], argv[2], atoi(argv[3]));
		printf("%d\n", res);
	}
	else
	{
		printf("wrong input\n");
	}
	return (0);
}*/
