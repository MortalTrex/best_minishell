/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:01 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/19 15:12:38 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char const	*ptr;

	ptr = NULL;
	while (*s)
	{
		if (*s == (char)c)
			ptr = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return ((char *)ptr);
}
/*
#include <stdio.h>
#include <string.h>
#include <stddef.h>
int main ()
{
  char str[] = "This is a sample string";
  char *pch;
  pch = ft_strrchr(str,'s');
  printf ("Last occurence of 's' found at %ld \n",pch-str+1);
  return 0;
}*/
