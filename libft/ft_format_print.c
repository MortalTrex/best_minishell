/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:23:54 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/02/13 15:03:20 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_put_nbr(long long int nb, int base, char *string)
{
	int				len;

	len = 0;
	if (nb == LONG_MIN)
		return (ft_put_str("-9223372036854775807"));
	if (nb < 0)
	{
		len += ft_put_char('-');
		nb = -nb;
	}
	if (nb >= (unsigned int)base)
	{
		len += ft_put_nbr(nb / base, base, string);
		len += ft_put_nbr(nb % base, base, string);
	}
	else
		len += ft_put_char(string[nb % base]);
	return (len);
}

int	ft_put_str(char *s)
{
	int	n;

	n = 0;
	if (!s)
		return (ft_put_str("(null)"));
	while (s[n] != '\0')
	{
		ft_put_char(s[n]);
		n++;
	}
	return (n);
}

int	ft_put_hexa(unsigned int nb, char c)
{
	int				len;
	int				base;

	len = 0;
	base = 16;
	if (c == 'x')
		len += ft_put_nbr(nb, base, "0123456789abcdef");
	else
		len += ft_put_nbr(nb, base, "0123456789ABCDEF");
	return (len);
}

int	ft_put_ptr(unsigned long long ptr)
{
	int			len;

	len = 0;
	if (ptr >= 16)
		len += ft_put_ptr(ptr / 16);
	len += ft_put_char("0123456789abcdef"[ptr % 16]);
	return (len);
}
