/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:17:34 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/24 15:42:38 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb && size && (size != size * nmemb / nmemb))
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


int main() {
    size_t num_elements = 5;
    size_t element_size = sizeof(int);

    // Allocate memory for an array of 5 integers and initialize to zero
    int *arr = (int *)ft_calloc(num_elements, element_size);

    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Access and use the allocated memory
    printf("Initial values:\n");
    for (size_t i = 0; i < num_elements; ++i) {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    // Modify the values
    for (size_t i = 0; i < num_elements; ++i) {
        arr[i] = i * 10; // Set values to 0, 10, 20, 30, 40
    }

    // Display the modified values
    printf("\nModified values:\n");
    for (size_t i = 0; i < num_elements; ++i) {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    // Don't forget to free the allocated memory when done using it
    free(arr);

    return 0;
}*/
