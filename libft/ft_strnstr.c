/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:48:02 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/24 14:38:20 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;

	len_little = ft_strlen(little);
	if (!little || *little == '\0')
		return ((char *) big);
	if (len <= 0)
		return (NULL);
	while (*big && len >= len_little)
	{
		while (*big == *little && ft_strncmp(big, little, len_little) == 0)
			return ((char *) big);
		big++;
		len--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
#include <stddef.h>
int main() {
    const char *haystack = "Hello, world! This is a test.";
    const char *needle = "world";

    char *result = ft_strnstr(haystack, needle, strlen(haystack));

    if (result) {
        printf("Needle found at position: %ld\n", result - haystack);
    } else {
        printf("Needle not found.\n");
    }

    return 0;
}*/
