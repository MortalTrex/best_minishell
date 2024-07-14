/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:08:07 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/24 15:17:46 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*chr1;
	unsigned char	*chr2;

	chr1 = (unsigned char *)s1;
	chr2 = (unsigned char *)s2;
	while (n--)
	{
		if (*chr1 != *chr2)
			return (*chr1 - *chr2);
		chr1++;
		chr2++;
	}
	return (0);
}
