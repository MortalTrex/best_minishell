/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:17:16 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/24 15:16:21 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	d_len;
	unsigned int	s_len;

	i = 0;
	s_len = ft_strlen(src);
	if (size == 0)
		return (s_len);
	d_len = ft_strlen(dst);
	if (size <= d_len)
		return (size + s_len);
	while (src[i] && i + d_len < size - 1)
	{
		dst[i + d_len] = src[i];
		i++;
	}
	dst[i + d_len] = '\0';
	return (d_len + s_len);
}

/*
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        printf("string is %d\n", ft_strlcat(argv[1], argv[2], atoi(argv[3])));
    }
    else
    {
        printf("wrong input\n");
    }
    return (0);
}*/
