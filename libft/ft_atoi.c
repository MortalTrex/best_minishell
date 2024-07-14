/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:10:01 by mmiilpal          #+#    #+#             */
/*   Updated: 2023/11/23 17:05:51 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (sign * (int)nb);
}

/*
#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		printf("%d\n", ft_atoi(argv[1]));
		return (0);
	}
	else
	{
		printf("input error");
		return (0);
	}
	return(0);
}*/
