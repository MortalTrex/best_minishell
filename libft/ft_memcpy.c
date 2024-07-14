/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:57:23 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/29 13:23:17 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d_ptr;
	char	*s_ptr;

	i = 0;
	if (!dst && !src)
		return (dst);
	d_ptr = (char *)dst;
	s_ptr = (char *)src;
	while (i < n)
	{
		d_ptr[i] = s_ptr[i];
		i++;
	}
	return (dst);
}
