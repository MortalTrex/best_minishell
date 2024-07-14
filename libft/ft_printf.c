/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:50:34 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/02/13 15:06:25 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printfformat(va_list arguments, const char format)
{
	unsigned long	ptr;

	if (format == 'c')
		return (ft_put_char(va_arg(arguments, int)));
	else if (format == 's')
		return (ft_put_str(va_arg(arguments, char *)));
	else if (format == 'p')
	{
		ptr = va_arg(arguments, unsigned long);
		if (!ptr)
			return (ft_put_str("(nil)"));
		ft_put_str("0x");
		return (ft_put_ptr(ptr) + 2);
	}
	else if (format == 'd')
		return (ft_put_nbr(va_arg(arguments, int), 10, "0123456789"));
	else if (format == 'i')
		return (ft_put_nbr(va_arg(arguments, int), 10, "0123456789"));
	else if (format == 'u')
		return (ft_put_nbr(va_arg(arguments, unsigned int), 10, "0123456789"));
	else if (format == 'x' || format == 'X')
		return (ft_put_hexa(va_arg(arguments, unsigned int), format));
	else if (format == '%')
		return (ft_put_char('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	arguments;
	int		len;

	len = 0;
	if (!format)
		return (-1);
	va_start(arguments, format);
	while (*(format))
	{
		if (*format == '%' && ft_strchr("cspdiuxX%", *(format + 1)))
		{
			len = len + ft_printfformat(arguments, *(format + 1));
			format++;
		}
		else
			len = len + ft_put_char(*format);
		format++;
	}
	va_end(arguments);
	return (len);
}
