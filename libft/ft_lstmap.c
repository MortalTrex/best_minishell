/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:13:18 by rbalazs           #+#    #+#             */
/*   Updated: 2023/12/13 11:46:22 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_a;
	t_list	*lst_b;

	lst_b = NULL;
	while (lst != NULL)
	{
		lst_a = ft_lstnew((*f)(lst->content));
		if (lst_a == NULL)
		{
			ft_lstclear(&lst_b, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_b, lst_a);
		lst = lst->next;
	}
	return (lst_b);
}
