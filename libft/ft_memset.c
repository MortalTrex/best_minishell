/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:55:33 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/15 15:06:45 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *) s;
	while (i < len)
	{
		*ptr = (unsigned char)c;
		ptr++;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
    char str[50] = "GeeksForGeeks is for programming geeks.";
    printf("\nBefore memset(): %s\n", str);


    // Fill 8 characters starting from str[13] with '.'
    ft_memset(str + 13, '.', 8*sizeof(char));

    printf("After memset():  %s", str);
    return 0;
}*/
