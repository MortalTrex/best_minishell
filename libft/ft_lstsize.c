/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:09:54 by rbalazs           #+#    #+#             */
/*   Updated: 2023/12/13 11:09:56 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

/*
#include <stdio.h>
int main() {
    t_list *head = malloc(sizeof(t_list));
    t_list *second = malloc(sizeof(t_list));
    t_list *third = malloc(sizeof(t_list));

    if (!head || !second || !third)
        return EXIT_FAILURE;

    head->content = NULL;
    head->next = second;

    second->content = NULL;
    second->next = third;

    third->content = NULL;
    third->next = NULL;

    int size = ft_lstsize(head);

    printf("Taille de la liste : %d\n", size);

    free(head);
    free(second);
    free(third);
}
*/
