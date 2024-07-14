/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:07:58 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/19 16:55:51 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
    char str[50] = "GeeksForGeeks is for programming geeks.";
    printf("\nBefore memset(): %s\n", str);


    // Fill 8 characters starting from str[13] with '.'
    memset(str + 13, '.', 8*sizeof(char));

    printf("After memset():  %s\n", str);

	ft_bzero(str+12, 8*sizeof(char));

    return 0;
}*/
