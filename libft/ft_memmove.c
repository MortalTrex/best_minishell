/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:00:21 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/24 15:38:40 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d_ptr;
	char	*s_ptr;
	size_t	i;

	d_ptr = (char *)dest;
	s_ptr = (char *)src;
	i = 0;
	if (!d_ptr && !s_ptr)
		return (NULL);
	while (n--)
	{
		if (dest > src)
			d_ptr[n] = s_ptr[n];
		else
		{
			d_ptr[i] = s_ptr[i];
			i++;
		}
	}
	return (dest);
}
