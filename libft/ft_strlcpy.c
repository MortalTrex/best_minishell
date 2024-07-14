/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari <mari@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:51:14 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/20 20:50:57 by mari             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

/*
#include <stdio.h>

int	main(void)
{
	unsigned int	i;

	i = 5;
	char    src[] = "Lunchtime doubly so.";
	char    dst[] = "Time is an illusion.";
	printf("%u", ft_strlcpy(dst, src, i));
	return (0);
}*/
