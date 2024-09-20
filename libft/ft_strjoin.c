/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:59:10 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/09/17 16:58:23 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*str_ptr;

	if (!s1 || !s2)
		return (NULL);
	str = (char *) malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	str_ptr = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str_ptr);
}

/*
#include <stdlib.h>
#include <stdio.h>

int main() {
    // Test strings
    const char *string1 = "Hello, ";
    const char *string2 = "World!";

    // Test the ft_strjoin function
    char *resultString = ft_strjoin(string1, string2);

    // Print the results
    printf("String 1: %s\n", string1);
    printf("String 2: %s\n", string2);
    printf("Joined String: %s\n", resultString);

    // Free the memory allocated for the result string
    free(resultString);

    return 0;
}*/
