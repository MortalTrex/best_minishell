/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:35:31 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 16:30:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *string)
{
	size_t	n;

	n = 0;
	while (string[n])
		n++;
	return (n);
}

/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char	*str;

	if (argc == 2)
	{
		str = argv[1];
		printf("%ld\n", ft_strlen(str));
	}
	else
	{
		return (printf("input error"), 0);
	}
	return (0);
}*/
