/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:41:35 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/29 14:56:45 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
// Example function to be applied in ft_strmapi
char example_mapping(unsigned int index, char c) {
    // Add 1 to the ASCII value of each character
    return c + 1;
}

int main() {
    // Test string
    const char *inputString = "Hello, World!";

    // Test the ft_strmapi function with the example_mapping function
    char *resultString = ft_strmapi(inputString, &example_mapping);

    // Print the results
    printf("Original String: %s\n", inputString);
    printf("Mapped String  : %s\n", resultString);

    // Free the memory allocated for the result string
    free(resultString);

    return 0;
}*/
