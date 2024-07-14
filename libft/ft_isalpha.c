/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:10:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/12 18:20:35 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (1);
	}
	if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	return (0);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argv)
	{
		char	chr = '3';
		printf("%d\n", ft_isalpha(chr));
	}
	return (0);
}*/
